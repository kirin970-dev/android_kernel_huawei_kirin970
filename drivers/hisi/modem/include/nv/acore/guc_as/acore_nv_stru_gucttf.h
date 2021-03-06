/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */


#ifndef __ACORE_NV_STRU_GUCTTF_H__
#define __ACORE_NV_STRU_GUCTTF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "nv_stru_gucttf.h"
#include "acore_nv_id_gucttf.h"

/*****************************************************************************
 ??????    : NV_TTF_PPP_CONFIG_STRU
 DESCRIPTION: ????en_NV_Item_PPP_CONFIG????????
*****************************************************************************/
typedef struct
{
    TTF_BOOL_ENUM_UINT8                 enChapEnable;           /* ????????Chap???? */
    TTF_BOOL_ENUM_UINT8                 enPapEnable;            /* ????????Pap???? */
    VOS_UINT16                          usLcpEchoMaxLostCnt;    /* ????LcpEchoRequest?????????????????? */

    VOS_UINT16                          usQueneMaxCnt;          /* ???????????????? */
    VOS_UINT8                           aucRsv[2];
}NV_TTF_PPP_CONFIG_STRU;

/*****************************************************************************
 ??????    : CPULOAD_CFG_STRU
 DESCRIPTION: ????en_NV_Item_Linux_CPU_Moniter_Timer_Len????????,A??CPU??????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMonitorTimerLen;
} CPULOAD_CFG_STRU;

/*****************************************************************************
 ??????    : FC_CPU_DRV_ASSEM_PARA_NV_STRU
 DESCRIPTION: ????en_NV_Item_FC_ACPU_DRV_ASSEMBLE_PARA??????????????CPU LOAD????????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                              ucEnableMask;                        /* ??????????0x0:????????0x1:???? */
    VOS_UINT8                              ucSmoothCntUpLev;                    /* ???????????????? */
    VOS_UINT8                              ucSmoothCntDownLev;                  /* ???????????????? */
    VOS_UINT8                              ucRsv;
    FC_CPU_DRV_ASSEM_PARA_STRU             stCpuDrvAssemPara[FC_ACPU_DRV_ASSEM_NV_LEV]; /* CPU???????? */
}FC_CPU_DRV_ASSEM_PARA_NV_STRU;

/*****************************************************************************
 ??????    : NF_EXT_NV_STRU
 DESCRIPTION: ????en_NV_Item_NETFILTER_HOOK_MASK????????,????????????NV????????5??????????:
             ulNvValue1~ulNvValue5, ??????????????????0-FFFFFFFF,
             ????????????1????????????????????????????????????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulNetfilterPara1;                                       /* ????????????????1 */
    VOS_UINT32          ulNetfilterPara2;                                       /* ????????????????2 */
    VOS_UINT32          ulNetfilterPara3;                                       /* ????????????????3 */
    VOS_UINT32          ulNetfilterPara4;                                       /* ????????????????4 */
    VOS_UINT32          ulNetfilterPara5;                                       /* ????????????????5 */
}NF_EXT_NV_STRU;

/*****************************************************************************
??????    : PPP_CONFIG_MRU_TYPE_NV_STRU
DESCRIPTION: ????en_NV_Item_PPP_CONFIG_MRU_Type????????,????????MTU??????????PPP LCP????
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           usPppConfigType;   /* ????MRU????,Range:[296,1500]*/
    VOS_UINT8                            aucReserve[2];
}PPP_CONFIG_MRU_TYPE_NV_STRU;

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __ACORE_NV_ID_GUCTTF_H__ */

