/*! \file bcm56960_a0_tm_scheduler.c
 *
 * Scheduler related api and function for bcm56960_a0.
 */
/*
 * Copyright: (c) 2018 Broadcom. All Rights Reserved. "Broadcom" refers to 
 * Broadcom Limited and/or its subsidiaries.
 * 
 * Broadcom Switch Software License
 * 
 * This license governs the use of the accompanying Broadcom software. Your 
 * use of the software indicates your acceptance of the terms and conditions 
 * of this license. If you do not agree to the terms and conditions of this 
 * license, do not use the software.
 * 1. Definitions
 *    "Licensor" means any person or entity that distributes its Work.
 *    "Software" means the original work of authorship made available under 
 *    this license.
 *    "Work" means the Software and any additions to or derivative works of 
 *    the Software that are made available under this license.
 *    The terms "reproduce," "reproduction," "derivative works," and 
 *    "distribution" have the meaning as provided under U.S. copyright law.
 *    Works, including the Software, are "made available" under this license 
 *    by including in or with the Work either (a) a copyright notice 
 *    referencing the applicability of this license to the Work, or (b) a copy 
 *    of this license.
 * 2. Grant of Copyright License
 *    Subject to the terms and conditions of this license, each Licensor 
 *    grants to you a perpetual, worldwide, non-exclusive, and royalty-free 
 *    copyright license to reproduce, prepare derivative works of, publicly 
 *    display, publicly perform, sublicense and distribute its Work and any 
 *    resulting derivative works in any form.
 * 3. Grant of Patent License
 *    Subject to the terms and conditions of this license, each Licensor 
 *    grants to you a perpetual, worldwide, non-exclusive, and royalty-free 
 *    patent license to make, have made, use, offer to sell, sell, import, and 
 *    otherwise transfer its Work, in whole or in part. This patent license 
 *    applies only to the patent claims licensable by Licensor that would be 
 *    infringed by Licensor's Work (or portion thereof) individually and 
 *    excluding any combinations with any other materials or technology.
 *    If you institute patent litigation against any Licensor (including a 
 *    cross-claim or counterclaim in a lawsuit) to enforce any patents that 
 *    you allege are infringed by any Work, then your patent license from such 
 *    Licensor to the Work shall terminate as of the date such litigation is 
 *    filed.
 * 4. Redistribution
 *    You may reproduce or distribute the Work only if (a) you do so under 
 *    this License, (b) you include a complete copy of this License with your 
 *    distribution, and (c) you retain without modification any copyright, 
 *    patent, trademark, or attribution notices that are present in the Work.
 * 5. Derivative Works
 *    You may specify that additional or different terms apply to the use, 
 *    reproduction, and distribution of your derivative works of the Work 
 *    ("Your Terms") only if (a) Your Terms provide that the limitations of 
 *    Section 7 apply to your derivative works, and (b) you identify the 
 *    specific derivative works that are subject to Your Terms. 
 *    Notwithstanding Your Terms, this license (including the redistribution 
 *    requirements in Section 4) will continue to apply to the Work itself.
 * 6. Trademarks
 *    This license does not grant any rights to use any Licensor's or its 
 *    affiliates' names, logos, or trademarks, except as necessary to 
 *    reproduce the notices described in this license.
 * 7. Limitations
 *    Platform. The Work and any derivative works thereof may only be used, or 
 *    intended for use, with a Broadcom switch integrated circuit.
 *    No Reverse Engineering. You will not use the Work to disassemble, 
 *    reverse engineer, decompile, or attempt to ascertain the underlying 
 *    technology of a Broadcom switch integrated circuit.
 * 8. Termination
 *    If you violate any term of this license, then your rights under this 
 *    license (including the license grants of Sections 2 and 3) will 
 *    terminate immediately.
 * 9. Disclaimer of Warranty
 *    THE WORK IS PROVIDED "AS IS" WITHOUT WARRANTIES OR CONDITIONS OF ANY 
 *    KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WARRANTIES OR CONDITIONS OF 
 *    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE OR 
 *    NON-INFRINGEMENT. YOU BEAR THE RISK OF UNDERTAKING ANY ACTIVITIES UNDER 
 *    THIS LICENSE. SOME STATES' CONSUMER LAWS DO NOT ALLOW EXCLUSION OF AN 
 *    IMPLIED WARRANTY, SO THIS DISCLAIMER MAY NOT APPLY TO YOU.
 * 10. Limitation of Liability
 *    EXCEPT AS PROHIBITED BY APPLICABLE LAW, IN NO EVENT AND UNDER NO LEGAL 
 *    THEORY, WHETHER IN TORT (INCLUDING NEGLIGENCE), CONTRACT, OR OTHERWISE 
 *    SHALL ANY LICENSOR BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY DIRECT, 
 *    INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF 
 *    OR RELATED TO THIS LICENSE, THE USE OR INABILITY TO USE THE WORK 
 *    (INCLUDING BUT NOT LIMITED TO LOSS OF GOODWILL, BUSINESS INTERRUPTION, 
 *    LOST PROFITS OR DATA, COMPUTER FAILURE OR MALFUNCTION, OR ANY OTHER 
 *    COMMERCIAL DAMAGES OR LOSSES), EVEN IF THE LICENSOR HAS BEEN ADVISED OF 
 *    THE POSSIBILITY OF SUCH DAMAGES.
 */

#include <shr/shr_debug.h>
#include <bcmtm/bcmtm_drv.h>
#include <bcmtm/bcmtm_types.h>
#include <bcmltd/bcmltd_types.h>
#include <bcmdrd/bcmdrd_types.h>
#include <bcmdrd/chip/bcm56960_a0_enum.h>
#include <bcmtm/bcmtm_pt_internal.h>
#include <bcmtm/sched_shaper/bcmtm_scheduler_internal.h>
#include "bcm56960_a0_tm_scheduler_shaper.h"
/*******************************************************************************
 * Local definitions
 */
extern bcmtm_scheduler_hdlr_t bcmtm_scheduler_hdlr[BCMDRD_DEV_T_COUNT];

/*******************************************************************************
 * Private functions
 */
static int
bcm56960_a0_tm_scheduler_node_set(int unit,
                                  bcmtm_lport_t lport,
                                  uint32_t node_id,
                                  uint32_t sched_level,
                                  bcmltd_sid_t ltid,
                                  bcmtm_scheduler_cfg_t *scheduler_cfg)
{
    bcmdrd_sid_t sid;
    bcmdrd_fid_t fid;
    uint32_t ltmbuf[BCMTM_MAX_ENTRY_WSIZE] = {0};
    uint32_t fval =0, wrr_mask;
    int mport, pipe, idx;
    bcmbd_pt_dyn_info_t pt_dyn_info;

    SHR_FUNC_ENTER(unit);

    SHR_IF_ERR_EXIT(bcmtm_port_mmu_local_port_get(unit, lport, &mport));
    SHR_IF_ERR_EXIT(bcmtm_port_pipe_get(unit, lport, &pipe));

    /* scheduler weight */
    if (sched_level == 0) {
        /* L0 Level */
        sid = Q_SCHED_L0_WEIGHT_MEMm;
        idx = mport * 10 + node_id;
    } else {
        /* L1 Level */
        sid = Q_SCHED_L1_WEIGHT_MEMm;
        if(bcmtm_port_is_mgmt(unit, lport)) {
            idx = ((sched_level == 1) ?
                    TH_MGMT_UCQ_OFFSET : TH_MGMT_MCQ_OFFSET)+ node_id;
        } else if (bcmtm_port_is_lb(unit, lport)) {
            idx = TH_LB_MCQ_OFFSET + node_id;
        } else {
            idx = (mport * 10 ) + node_id +
                ((sched_level == 1) ? 0 : TH_NUM_UC_QUEUES_PER_PIPE);
        }
    }
    fid = WEIGHTf;
    fval = scheduler_cfg->weight;

    BCMTM_PT_DYN_INFO(pt_dyn_info, idx, pipe);
    SHR_IF_ERR_EXIT
        (bcmtm_field_set(unit, sid, fid, ltmbuf, &fval));
    SHR_IF_ERR_EXIT
        (bcmtm_pt_indexed_write(unit, sid, ltid, &pt_dyn_info, ltmbuf));

    sal_memset(ltmbuf, 0, sizeof(uint32_t)*BCMTM_MAX_ENTRY_WSIZE);

    BCMTM_PT_DYN_INFO(pt_dyn_info, 0, mport);
    if (sched_level == 0) {
        sid = Q_SCHED_PORT_CONFIGr;
        idx = 0;
    } else {
        sid = Q_SCHED_L0_NODE_CONFIGr;
        idx = node_id;
    }
    if (scheduler_cfg->sched_mode == 1) {
        fval = 1;
    } else if (scheduler_cfg->sched_mode == 2) {
        fval = 0;
    }
    SHR_IF_ERR_EXIT
        (bcmtm_pt_indexed_read(unit, sid, ltid, &pt_dyn_info, ltmbuf));
    SHR_IF_ERR_EXIT
        (bcmtm_field_get(unit, sid, fid, ltmbuf, &wrr_mask));
    wrr_mask &= ~( 1 << idx);
    wrr_mask |= (fval << idx);
    SHR_IF_ERR_EXIT
        (bcmtm_field_set(unit, sid, fid, ltmbuf, &wrr_mask));
    SHR_IF_ERR_EXIT
        (bcmtm_pt_indexed_write(unit, sid, ltid, &pt_dyn_info, ltmbuf));
exit:
    SHR_FUNC_EXIT();
}

static int
bcm56960_a0_tm_scheduler_cpu_node_set(int unit,
                                      uint32_t node_id,
                                      uint32_t sched_level,
                                      bcmltd_sid_t ltid,
                                      bcmtm_scheduler_cfg_t *scheduler_cfg)
{
    bcmdrd_sid_t sid;
    bcmdrd_fid_t fid;
    uint32_t ltmbuf[BCMTM_MAX_ENTRY_WSIZE] = {0};
    uint32_t fval =0, wrr_mask;
    int idx, mport;
    bcmbd_pt_dyn_info_t pt_dyn_info;

    SHR_FUNC_ENTER(unit);

    if ((sched_level == 0) && (node_id >= TH_NUM_L0_NODE_PER_PORT)) {
        SHR_RETURN_VAL_EXIT(SHR_E_PARAM);
    }
    /* scheduler weight */
    if (sched_level == 0) {
        /* L0 Level */
        sid = Q_SCHED_L0_WEIGHT_MEMm;
        SHR_IF_ERR_EXIT
            (bcmtm_port_mmu_local_port_get(unit, 0, &mport));
        idx = mport * 10 + node_id;
    } else {
        /* L1 Level */
        sid = Q_SCHED_L1_WEIGHT_MEMm;
        idx = TH_CPU_MCQ_OFFSET + node_id;
    }
    fid = WEIGHTf;
    fval = scheduler_cfg->weight;

    BCMTM_PT_DYN_INFO(pt_dyn_info, idx, 0);
    SHR_IF_ERR_EXIT
        (bcmtm_field_set(unit, sid, fid, ltmbuf, &fval));
    SHR_IF_ERR_EXIT
        (bcmtm_pt_indexed_write(unit, sid, ltid, &pt_dyn_info, ltmbuf));

    sal_memset(ltmbuf, 0, sizeof(uint32_t)*BCMTM_MAX_ENTRY_WSIZE);

    BCMTM_PT_DYN_INFO(pt_dyn_info, 0, 0);
    if (sched_level == 0) {
        sid = Q_SCHED_CPU_PORT_CONFIGr;
        idx = 0;
    } else {
        sid = Q_SCHED_CPU_L0_NODE_CONFIGr;
        idx = scheduler_cfg->parent_node;
    }
    if (scheduler_cfg->sched_mode == 1) {
        fval = 1;
    } else if (scheduler_cfg->sched_mode == 2) {
        fval = 0;
    }
    SHR_IF_ERR_EXIT
        (bcmtm_pt_indexed_read(unit, sid, ltid, &pt_dyn_info, ltmbuf));
    SHR_IF_ERR_EXIT
        (bcmtm_field_get(unit, sid, fid, ltmbuf, &wrr_mask));
    wrr_mask &= ~( 1 << idx);
    wrr_mask |= (fval << idx);
    SHR_IF_ERR_EXIT
        (bcmtm_field_set(unit, sid, fid, ltmbuf, &wrr_mask));
    SHR_IF_ERR_EXIT
        (bcmtm_pt_indexed_write(unit, sid, ltid, &pt_dyn_info, ltmbuf));

    sal_memset(ltmbuf, 0, sizeof(uint32_t)*BCMTM_MAX_ENTRY_WSIZE);
    if (sched_level != 0) {
        sid = Q_SCHED_CPU_L1_MC_QUEUE_L0_MAPPINGr;
        fid = SELECTf;
        fval = scheduler_cfg->parent_node;
        BCMTM_PT_DYN_INFO(pt_dyn_info, node_id, 0);
        SHR_IF_ERR_EXIT
            (bcmtm_field_set(unit, sid, fid, ltmbuf, &fval));
        SHR_IF_ERR_EXIT
            (bcmtm_pt_indexed_write(unit, sid, ltid, &pt_dyn_info, ltmbuf));
    }
exit:
    SHR_FUNC_EXIT();
}

/*******************************************************************************
 * Public functions
 */
int
bcm56960_a0_tm_scheduler_fn_ptrs_init(int unit)
{
    bcmdrd_dev_type_t dev_type;

    SHR_FUNC_ENTER(unit);
    dev_type = bcmdrd_dev_type(unit);
    if (dev_type == BCMDRD_DEV_T_NONE) {
        SHR_IF_ERR_EXIT(SHR_E_UNIT);
    }
    /* scheduler physical table update. */
    bcmtm_scheduler_hdlr[dev_type].node_set = bcm56960_a0_tm_scheduler_node_set;
    bcmtm_scheduler_hdlr[dev_type].cpu_node_set =
                            bcm56960_a0_tm_scheduler_cpu_node_set;
exit:
    SHR_FUNC_EXIT();
}
