/*! \file bcmfp_em_policy_map.c
 *
 * APIs for Exact Match Policy LT fields to internal value mapping
 *
 * This file contains function definitions for Exact Match Policy LT template
 * fields to action  mapping.
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

/*******************************************************************************
  Includes
 */
#include <shr/shr_debug.h>
#include <bcmltd/chip/bcmltd_id.h>
#include <bcmfp/bcmfp_internal.h>
#include <bcmfp/map/bcmfp_lt_policy_map.h>

#define BSL_LOG_MODULE BSL_LS_BCMFP_COMMON

/*! Exact Match FP Policy Field Identifiers that needs individual handling. */
bcmfp_lt_policy_sp_fids_t bcmfp_em_policy_sp_fids = {
    .policy_id_fid = FP_EM_POLICY_TEMPLATEt_FP_EM_POLICY_TEMPLATE_IDf,
    .policy_fid_count = FP_EM_POLICY_TEMPLATEt_FIELD_COUNT
};

/*******************************************************************************
 * Public functions
 */
int
bcmfp_em_policy_init(int unit,
                      bcmfp_lt_info_t *lt_info)
{
    SHR_FUNC_ENTER(unit)

    lt_info->flags |= BCMFP_LT_FLAGS_INMEM_SUPPORT;
    lt_info->map_get = bcmfp_em_policy_action_map_get;
    lt_info->key_fid  = FP_EM_POLICY_TEMPLATEt_FP_EM_POLICY_TEMPLATE_IDf;
    lt_info->sp_fids = (void *) &bcmfp_em_policy_sp_fids;

    SHR_FUNC_EXIT();
}

/* Mapping of LT fields to Action */
int
bcmfp_em_policy_action_map_get(int unit,
                                uint32_t fid,
                                uint32_t idx,
                                void *map)
{
    bcmfp_action_t action;
    bcmfp_lt_policy_action_map_t *policy_map = NULL;
    SHR_FUNC_ENTER(unit);

    policy_map = (bcmfp_lt_policy_action_map_t *) map;

    switch(fid) {
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_DROPf:
            action = BCMFP_ACTION_R_DROP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_DROPf:
            action = BCMFP_ACTION_Y_DROP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_DROPf:
            action = BCMFP_ACTION_G_DROP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_UNTAG_PKT_PRIORITYf:
            action = BCMFP_ACTION_NEW_UNTAG_PKT_PRIORITY;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_R_COLORf:
            action = BCMFP_ACTION_NEW_R_COLOR;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_Y_COLORf:
            action = BCMFP_ACTION_NEW_Y_COLOR;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_G_COLORf:
            action = BCMFP_ACTION_NEW_G_COLOR;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_R_COS_MAPf:
            action = BCMFP_ACTION_NEW_R_COS_MAP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_INTPRI_TO_INNER_DOT1Pf:
            action = BCMFP_ACTION_R_INTPRI_TO_INNER_DOT1P;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_R_INTPRIf:
            action = BCMFP_ACTION_NEW_R_INTPRI;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_INTPRI_TO_TOSf:
            action = BCMFP_ACTION_R_INTPRI_TO_TOS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_INTPRI_UPDATES_CANCELf:
            action = BCMFP_ACTION_R_INTPRI_UPDATES_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_R_UC_COSf:
            action = BCMFP_ACTION_NEW_R_UC_COS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_R_MC_COSf:
            action = BCMFP_ACTION_NEW_R_MC_COS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_Y_COS_MAPf:
            action = BCMFP_ACTION_NEW_Y_COS_MAP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_INTPRI_TO_INNER_DOT1Pf:
            action = BCMFP_ACTION_Y_INTPRI_TO_INNER_DOT1P;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_Y_INTPRIf:
            action = BCMFP_ACTION_NEW_Y_INTPRI;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_INTPRI_TO_TOSf:
            action = BCMFP_ACTION_Y_INTPRI_TO_TOS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_INTPRI_UPDATES_CANCELf:
            action = BCMFP_ACTION_Y_INTPRI_UPDATES_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_Y_UC_COSf:
            action = BCMFP_ACTION_NEW_Y_UC_COS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_Y_MC_COSf:
            action = BCMFP_ACTION_NEW_Y_MC_COS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_G_COS_MAPf:
            action = BCMFP_ACTION_NEW_G_COS_MAP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_INTPRI_TO_INNER_DOT1Pf:
            action = BCMFP_ACTION_G_INTPRI_TO_INNER_DOT1P;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_G_INTPRIf:
            action = BCMFP_ACTION_NEW_G_INTPRI;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_INTPRI_TO_TOSf:
            action = BCMFP_ACTION_G_INTPRI_TO_TOS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_INTPRI_UPDATES_CANCELf:
            action = BCMFP_ACTION_G_INTPRI_UPDATES_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_G_UC_COSf:
            action = BCMFP_ACTION_NEW_G_UC_COS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_G_MC_COSf:
            action = BCMFP_ACTION_NEW_G_MC_COS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_HGT_SPRAY_HASH_CANCELf:
            action = BCMFP_ACTION_HGT_SPRAY_HASH_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_TRUNK_SPARY_HASH_CANCELf:
            action = BCMFP_ACTION_TRUNK_SPARY_HASH_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_ECMP_SPRAY_HASH_CANCELf:
            action = BCMFP_ACTION_ECMP_SPRAY_HASH_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_DO_NOT_NATf:
            action = BCMFP_ACTION_DO_NOT_NAT;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_MATCH_IDf:
            action = BCMFP_ACTION_MATCH_ID;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_COPY_TO_CPUf:
            action = BCMFP_ACTION_R_COPY_TO_CPU;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_COPY_TO_CPU_CANCELf:
            action = BCMFP_ACTION_R_COPY_TO_CPU_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_SWITCH_TO_CPU_CANCELf:
            action = BCMFP_ACTION_R_SWITCH_TO_CPU_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_SWITCH_TO_CPU_REINSATEf:
            action = BCMFP_ACTION_R_SWITCH_TO_CPU_REINSATE;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_COPY_TO_CPU_WITH_TIMESTAMPf:
            action = BCMFP_ACTION_R_COPY_TO_CPU_WITH_TIMESTAMP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_COPY_TO_CPUf:
            action = BCMFP_ACTION_Y_COPY_TO_CPU;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_COPY_TO_CPU_CANCELf:
            action = BCMFP_ACTION_Y_COPY_TO_CPU_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_SWITCH_TO_CPU_CANCELf:
            action = BCMFP_ACTION_Y_SWITCH_TO_CPU_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_SWITCH_TO_CPU_REINSATEf:
            action = BCMFP_ACTION_Y_SWITCH_TO_CPU_REINSATE;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_COPY_TO_CPU_WITH_TIMESTAMPf:
            action = BCMFP_ACTION_Y_COPY_TO_CPU_WITH_TIMESTAMP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_COPY_TO_CPUf:
            action = BCMFP_ACTION_G_COPY_TO_CPU;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_COPY_TO_CPU_CANCELf:
            action = BCMFP_ACTION_G_COPY_TO_CPU_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_SWITCH_TO_CPU_CANCELf:
            action = BCMFP_ACTION_G_SWITCH_TO_CPU_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_SWITCH_TO_CPU_REINSATEf:
            action = BCMFP_ACTION_G_SWITCH_TO_CPU_REINSATE;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_COPY_TO_CPU_WITH_TIMESTAMPf:
            action = BCMFP_ACTION_G_COPY_TO_CPU_WITH_TIMESTAMP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_DO_NOT_CUT_THROUGHf:
            action = BCMFP_ACTION_DO_NOT_CUT_THROUGH;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_DO_NOT_URPFf:
            action = BCMFP_ACTION_DO_NOT_URPF;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_DO_NOT_CHANGE_TTLf:
            action = BCMFP_ACTION_DO_NOT_CHANGE_TTL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_R_ECNf:
            action = BCMFP_ACTION_NEW_R_ECN;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_PRESERVE_DOT1Pf:
            action = BCMFP_ACTION_R_PRESERVE_DOT1P;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_OUTER_DOT1P_TO_INNER_DOT1Pf:
            action = BCMFP_ACTION_R_OUTER_DOT1P_TO_INNER_DOT1P;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_R_OUTER_DOT1Pf:
            action = BCMFP_ACTION_NEW_R_OUTER_DOT1P;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_OUTER_DOT1P_TO_TOSf:
            action = BCMFP_ACTION_R_OUTER_DOT1P_TO_TOS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_DOT1P_UPDATES_CANCELf:
            action = BCMFP_ACTION_R_DOT1P_UPDATES_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_Y_ECNf:
            action = BCMFP_ACTION_NEW_Y_ECN;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_PRESERVE_DOT1Pf:
            action = BCMFP_ACTION_Y_PRESERVE_DOT1P;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_OUTER_DOT1P_TO_INNER_DOT1Pf:
            action = BCMFP_ACTION_Y_OUTER_DOT1P_TO_INNER_DOT1P;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_Y_OUTER_DOT1Pf:
            action = BCMFP_ACTION_NEW_Y_OUTER_DOT1P;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_OUTER_DOT1P_TO_TOSf:
            action = BCMFP_ACTION_Y_OUTER_DOT1P_TO_TOS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_DOT1P_UPDATES_CANCELf:
            action = BCMFP_ACTION_Y_DOT1P_UPDATES_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_G_ECNf:
            action = BCMFP_ACTION_NEW_G_ECN;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_PRESERVE_DOT1Pf:
            action = BCMFP_ACTION_G_PRESERVE_DOT1P;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_OUTER_DOT1P_TO_INNER_DOT1Pf:
            action = BCMFP_ACTION_G_OUTER_DOT1P_TO_INNER_DOT1P;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_G_OUTER_DOT1Pf:
            action = BCMFP_ACTION_NEW_G_OUTER_DOT1P;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_OUTER_DOT1P_TO_TOSf:
            action = BCMFP_ACTION_G_OUTER_DOT1P_TO_TOS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_DOT1P_UPDATES_CANCELf:
            action = BCMFP_ACTION_G_DOT1P_UPDATES_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_R_DSCPf:
            action = BCMFP_ACTION_NEW_R_DSCP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_DSCP_UPDATES_CANCELf:
            action = BCMFP_ACTION_R_DSCP_UPDATES_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_PRESERVE_DSCPf:
            action = BCMFP_ACTION_R_PRESERVE_DSCP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_Y_DSCPf:
            action = BCMFP_ACTION_NEW_Y_DSCP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_DSCP_UPDATES_CANCELf:
            action = BCMFP_ACTION_Y_DSCP_UPDATES_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_PRESERVE_DSCPf:
            action = BCMFP_ACTION_Y_PRESERVE_DSCP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_G_DSCPf:
            action = BCMFP_ACTION_NEW_G_DSCP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_DSCP_UPDATES_CANCELf:
            action = BCMFP_ACTION_G_DSCP_UPDATES_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_PRESERVE_DSCPf:
            action = BCMFP_ACTION_G_PRESERVE_DSCP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_G_TOSf:
            action = BCMFP_ACTION_NEW_G_TOS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_TOS_TO_PRE_FP_ING_OUTER_DOT1Pf:
            action = BCMFP_ACTION_G_TOS_TO_PRE_FP_ING_OUTER_DOT1P;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_CHANGE_PKT_L2_FIELDSf:
            action = BCMFP_ACTION_CHANGE_PKT_L2_FIELDS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_CHANGE_PKT_L2_FIELDS_CANCELf:
            action = BCMFP_ACTION_CHANGE_PKT_L2_FIELDS_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_CLASSIFICATION_TAGf:
            action = BCMFP_ACTION_NEW_CLASSIFICATION_TAG;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_SWITCH_TO_L3UCf:
            action = BCMFP_ACTION_SWITCH_TO_L3UC;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_SWITCH_TO_ECMPf:
            action = BCMFP_ACTION_SWITCH_TO_ECMP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_L3_SWITCH_CANCELf:
            action = BCMFP_ACTION_L3_SWITCH_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_I2E_CLASSID_SELECTf:
            action = BCMFP_ACTION_I2E_CLASSID_SELECT;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_HIGIG_CLASSID_SELECTf:
            action = BCMFP_ACTION_HIGIG_CLASSID_SYSTEM_PORT;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_I2E_CLASSIDf:
            action = BCMFP_ACTION_NEW_I2E_CLASSID;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_BFD_SEESSION_IDXf:
            action = BCMFP_ACTION_NEW_BFD_SEESSION_IDX;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_CPU_COSf:
            action = BCMFP_ACTION_NEW_CPU_COS;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_SERVICE_POOL_IDf:
            action = BCMFP_ACTION_NEW_SERVICE_POOL_ID;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_R_DROP_CANCELf:
            action = BCMFP_ACTION_R_DROP_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_Y_DROP_CANCELf:
            action = BCMFP_ACTION_Y_DROP_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_G_DROP_CANCELf:
            action = BCMFP_ACTION_G_DROP_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_G_INTCNf:
            action = BCMFP_ACTION_NEW_G_INTCN;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_Y_INTCNf:
            action = BCMFP_ACTION_NEW_Y_INTCN;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_R_INTCNf:
            action = BCMFP_ACTION_NEW_R_INTCN;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_MIRROR_OVERRIDEf:
            action = BCMFP_ACTION_MIRROR_OVERRIDE;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_SFLOW_ENABLEf:
            action = BCMFP_ACTION_SFLOW_ENABLE;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_REDIRECT_TO_MODULEf:
            action = BCMFP_ACTION_REDIRECT_TO_MODULE;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_REDIRECT_TO_PORTf:
            action = BCMFP_ACTION_REDIRECT_TO_PORT;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_REDIRECT_TO_DVPf:
            action = BCMFP_ACTION_REDIRECT_TO_DVP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_REDIRECT_TO_TRUNKf:
            action = BCMFP_ACTION_REDIRECT_TO_TRUNK;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_UNMODIFIED_REDIRECT_TO_MODULEf:
            action = BCMFP_ACTION_UNMODIFIED_REDIRECT_TO_MODULE;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_UNMODIFIED_REDIRECT_TO_TRUNKf:
            action = BCMFP_ACTION_UNMODIFIED_REDIRECT_TO_TRUNK;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_UNMODIFIED_REDIRECT_TO_PORTf:
            action = BCMFP_ACTION_UNMODIFIED_REDIRECT_TO_PORT;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_REDIRECT_TO_NHOPf:
            action = BCMFP_ACTION_REDIRECT_TO_NHOP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_REDIRECT_TO_ECMPf:
            action = BCMFP_ACTION_REDIRECT_TO_ECMP;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_REDIRECT_UC_CANCELf:
            action = BCMFP_ACTION_REDIRECT_UC_CANCEL;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NEW_HIGIG_EHf:
            action = BCMFP_ACTION_NEW_HIGIG_EH;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_HIGIG_EH_MASK_PROFILE_IDf:
            action = BCMFP_ACTION_HIGIG_EH_MASK_PROFILE_ID;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_NAT_EGR_OVERRIDEf:
            action = BCMFP_ACTION_NAT_EGRESS_OVERRIDE;
            break;
        case FP_EM_POLICY_TEMPLATEt_ACTION_EXACT_MATCH_CLASS_IDf:
            action = BCMFP_ACTION_EXACT_MATCH_CLASS_ID;
            break;
        default:
            SHR_RETURN_VAL_EXIT(SHR_E_NOT_FOUND);
    }

    policy_map->fid = fid;
    policy_map->action = action;

exit:

    SHR_FUNC_EXIT();
}
