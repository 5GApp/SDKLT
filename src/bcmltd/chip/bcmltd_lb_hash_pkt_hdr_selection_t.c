/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated by fltg from INTERNAL/fltg/xgs/lb_hash/LB_HASH_PKT_HDR_SELECTION.tbl.ltl
 * Edits to this file will be lost when it is regenerated.
 *
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
#include <bcmltd/bcmltd_internal.h>
#include "bcmltd_strpool.h"
static const bcmltd_field_rep_t bcmltd_lb_hash_pkt_hdr_selection_t_fields[] = {
    {
        .name  = bcmltd_strpool_hash0_ignore_ipv4,  /* HASH0_IGNORE_IPV4 */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Enable hash selection for IPv4 packets default to Ethernet\n packets for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_ipv4,  /* HASH1_IGNORE_IPV4 */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_ipv6,  /* HASH0_IGNORE_IPV6 */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Enable hash selection for IPv6 packets default to Ethernet\n packets for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_ipv6,  /* HASH1_IGNORE_IPV6 */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_inner_4over4_ip_tunnel,  /* HASH0_IGNORE_INNER_4OVER4_IP_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Disable hashing based on inner IPv4 packet header for IPv4 over IPv4\n packets (outer ip.protocol = 4) for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_inner_4over4_ip_tunnel,  /* HASH1_IGNORE_INNER_4OVER4_IP_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_inner_6over4_ip_tunnel,  /* HASH0_IGNORE_INNER_6OVER4_IP_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Disable hashing based on inner IPv6 packet header for\n IPv6 over IPv4 packets for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_inner_6over4_ip_tunnel,  /* HASH1_IGNORE_INNER_6OVER4_IP_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_inner_4over4_gre_tunnel,  /* HASH0_IGNORE_INNER_4OVER4_GRE_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Disable hashing based on inner IPv4 packet header for\n IPv4 over GRE-IPv4 packets (outer ip.protocol = 47)\n for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_inner_4over4_gre_tunnel,  /* HASH1_IGNORE_INNER_4OVER4_GRE_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_inner_6over4_gre_tunnel,  /* HASH0_IGNORE_INNER_6OVER4_GRE_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Disable hashing based on inner IPv6 packet header for\n IPv6 over GRE-IPv4 packets (outer ip.protocol = 47)\n for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_inner_6over4_gre_tunnel,  /* HASH1_IGNORE_INNER_6OVER4_GRE_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_inner_4over6_ip_tunnel,  /* HASH0_IGNORE_INNER_4OVER6_IP_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Disable hashing based on inner IPv4 packet header for\n IPv4 over IPv6 packets for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_inner_4over6_ip_tunnel,  /* HASH1_IGNORE_INNER_4OVER6_IP_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_inner_6over6_ip_tunnel,  /* HASH0_IGNORE_INNER_6OVER6_IP_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Disable hashing based on inner IPv6 packet header for\n IPv6 over IPv6 packets for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_inner_6over6_ip_tunnel,  /* HASH1_IGNORE_INNER_6OVER6_IP_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_inner_6over6_gre_tunnel,  /* HASH0_IGNORE_INNER_6OVER6_GRE_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Disable hashing based on inner IPv6 packet header for\n IPv6 over GRE-IPv6 packets (outer ip.protocol = 47)\n for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_inner_6over6_gre_tunnel,  /* HASH1_IGNORE_INNER_6OVER6_GRE_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_inner_4over6_gre_tunnel,  /* HASH0_IGNORE_INNER_4OVER6_GRE_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Disable hashing based on inner IPv4 packet header for\n IPv4 over GRE-IPv6 packets (outer ip.protocol = 47)\n for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_inner_4over6_gre_tunnel,  /* HASH1_IGNORE_INNER_4OVER6_GRE_TUNNEL */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_mpls,  /* HASH0_IGNORE_MPLS */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Enable hash selection for MPLS packets default to Ethernet\n packets for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_mpls,  /* HASH1_IGNORE_MPLS */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_mim,  /* HASH0_IGNORE_MIM */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Enable hash selection for MiM packets default to Ethernet\n packets for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_mim,  /* HASH1_IGNORE_MIM */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_fcoe,  /* HASH0_IGNORE_FCOE */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Enable to hash based on outer L2 fields for hash key 0 or 1.\n Disable to hash based on FCoE headers for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_fcoe,  /* HASH1_IGNORE_FCOE */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_l2gre,  /* HASH0_IGNORE_L2GRE */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Enable hash selection for L2 GRE packets default to Ethernet\n packets for hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_l2gre,  /* HASH1_IGNORE_L2GRE */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_mim_use_tunnel_header,  /* HASH0_MIM_USE_TUNNEL_HEADER */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Enable to use tunnel header fields for MiM trafic for\n hash key 0 or 1.\n Disable to use payload fields for MiM traffic for\n hash key 0 or 1.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_mim_use_tunnel_header,  /* HASH1_MIM_USE_TUNNEL_HEADER */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_hash0_ignore_vxlan,  /* HASH0_IGNORE_VXLAN */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Enable hashing based on outer L3 header fields,\n if that is also disabled then it will default to\n outer L2 header fields.\n",
    },
    {
        .name  = bcmltd_strpool_hash1_ignore_vxlan,  /* HASH1_IGNORE_VXLAN */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "",
    },
    {
        .name  = bcmltd_strpool_ignore_ip_extn_hdr,  /* IGNORE_IP_EXTN_HDR */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Enable hashing to use protocol directly from IP header,\n ignoring presence of extension headers.\n Disable hashing to use 'last next header' in protocol bucket.\n",
    },
    {
        .name  = bcmltd_strpool_ignore_mpls_reserved_labels,  /* IGNORE_MPLS_RESERVED_LABELS */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Enable hashing to exclude reserved MPLS labels.",
    },
    {
        .name  = bcmltd_strpool_hash_use_mpls_stack,  /* HASH_USE_MPLS_STACK */
        .flags = 0,
        .width = 1,
        .depth = 0,
        .desc = "Enable to hash on up to the top 5 tunnel labels for MPLS.\n Disable to hash on up to the top 3 tunnel labels + tunnel payload\n IPv4\n",
    },
};
const bcmltd_table_rep_t bcmltd_lb_hash_pkt_hdr_selection_t = {
    .name = bcmltd_strpool_lb_hash_pkt_hdr_selection, /* LB_HASH_PKT_HDR_SELECTION */
    .flags = 0,
    .fields = 35,
    .field = bcmltd_lb_hash_pkt_hdr_selection_t_fields,
    .desc = "The LB_HASH_PKT_HDR_SELECTION table specifies the packet header selection\n for various packet types.\n",
};
