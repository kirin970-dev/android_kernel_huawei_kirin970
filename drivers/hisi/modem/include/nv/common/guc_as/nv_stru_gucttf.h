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


#ifndef __NV_STRU_GUCTTF_H__
#define __NV_STRU_GUCTTF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "nv_id_gucttf.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define FC_UL_RATE_MAX_LEV                  (11)
#define FC_ACPU_DRV_ASSEM_NV_LEV            (4)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

enum FC_ACPU_DRV_ASSEM_LEV_ENUM
{
    FC_ACPU_DRV_ASSEM_LEV_1             = 0,
    FC_ACPU_DRV_ASSEM_LEV_2,
    FC_ACPU_DRV_ASSEM_LEV_3,
    FC_ACPU_DRV_ASSEM_LEV_4,
    FC_ACPU_DRV_ASSEM_LEV_5             = 4,
    FC_ACPU_DRV_ASSEM_LEV_BUTT          = 5
};
typedef VOS_UINT32  FC_ACPU_DRV_ASSEM_LEV_ENUM_UINT32;


enum FC_MEM_THRESHOLD_LEV_ENUM
{
    FC_MEM_THRESHOLD_LEV_1              = 0,
    FC_MEM_THRESHOLD_LEV_2,
    FC_MEM_THRESHOLD_LEV_3,
    FC_MEM_THRESHOLD_LEV_4,
    FC_MEM_THRESHOLD_LEV_5,
    FC_MEM_THRESHOLD_LEV_6,
    FC_MEM_THRESHOLD_LEV_7,
    FC_MEM_THRESHOLD_LEV_8,
    FC_MEM_THRESHOLD_LEV_BUTT           = 8
};
typedef VOS_UINT32  FC_MEM_THRESHOLD_LEV_ENUM_UINT32;

/*****************************************************************************
 ??????    : TTF_BOOL_ENUM
 ????????  :
 ASN.1???? :
 ????????  : TTF????????????????????
*****************************************************************************/
enum TTF_BOOL_ENUM
{
    TTF_FALSE                            = 0,
    TTF_TRUE                             = 1,

    TTF_BOOL_BUTT
};
typedef VOS_UINT8   TTF_BOOL_ENUM_UINT8;

/*****************************************************************************
 ??????    : FC_CPU_DRV_ASSEM_PARA_STRU
 DESCRIPTION: ????CPU LOAD????????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucHostOutTimeout;    /* PC???????????? */
    VOS_UINT8                          ucEthTxMinNum;       /* UE???????????????? */
    VOS_UINT8                          ucEthTxTimeout;      /* UE???????????????? */
    VOS_UINT8                          ucEthRxMinNum;       /* UE???????????????? */
    VOS_UINT8                          ucEthRxTimeout;      /* UE???????????????? */
    VOS_UINT8                          ucCdsGuDlThres;      /* ?????? */
    VOS_UINT8                          aucRsv[2];
}FC_DRV_ASSEM_PARA_STRU;

/*****************************************************************************
 ??????    : FC_CPU_DRV_ASSEM_PARA_STRU
 DESCRIPTION: ????CPU LOAD????????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCpuLoad;                              /* CPU????,Range:[0,100] */
    FC_DRV_ASSEM_PARA_STRU              stDrvAssemPara;
}FC_CPU_DRV_ASSEM_PARA_STRU;

/*****************************************************************************
 ??????    : FC_CFG_CPU_STRU
 DESCRIPTION: FC_CFG_CPU????,CPU??????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCpuOverLoadVal;                       /*Range:[0,100]*//* CPU???????? */
    VOS_UINT32                          ulCpuUnderLoadVal;                      /*Range:[0,100]*//* CPU???????????? */
    VOS_UINT32                          ulSmoothTimerLen;                       /*Range:[2,1000]*//* CPU??????????????????:CPU???????? */
    VOS_UINT32                          ulStopAttemptTimerLen;                  /* CPU????R????????????????????????????????????????????????????????????: ??????0?????????? */
    VOS_UINT32                          ulUmUlRateThreshold;                    /* ??????????????????????????????????????????????CPU???????????????? */
    VOS_UINT32                          ulUmDlRateThreshold;                    /* ??????????????????????????????????????????????CPU???????????????? */
    VOS_UINT32                          ulRmRateThreshold;                      /* E5???????? WIFI/USB???????????????? ????????????????????????????CPU??????????????????????bps */
} FC_CFG_CPU_STRU;

/*****************************************************************************
 ??????    : FC_CFG_MEM_THRESHOLD_STRU
 DESCRIPTION: FC_CFG_MEM_THRESHOLD????,MEM??????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSetThreshold;                         /* ???????????? ???????? */
    VOS_UINT32                          ulStopThreshold;                        /* ???????????? ???????? */
} FC_CFG_MEM_THRESHOLD_STRU;

/*****************************************************************************
 ??????    : FC_CFG_MEM_THRESHOLD_CST_STRU
 DESCRIPTION: FC_CFG_MEM_THRESHOLD_CST????,MEM??????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSetThreshold;                         /*Range:[0,4096]*//* ???????????? ???????? */
    VOS_UINT32                          ulStopThreshold;                        /*Range:[0,4096]*//* ???????????? ???????? */
} FC_CFG_MEM_THRESHOLD_CST_STRU;

/*****************************************************************************
 ??????    : FC_CFG_UM_UL_RATE_STRU
 DESCRIPTION: FC_CFG_UM_UL_RATE????,????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRateCnt;                              /*Range:[0,11]*//* ??????????????????????????11????????????????????????????FC_PRI_9??????????????????????9?????? */
    VOS_UINT8                           aucRsv[1];
    VOS_UINT16                          ausRate[FC_UL_RATE_MAX_LEV];            /* ??????????????????????[0,65535]??????bps */
} FC_CFG_UM_UL_RATE_STRU;

/*****************************************************************************
 ??????    : FC_CFG_NV_STRU
 DESCRIPTION: ????en_NV_Item_Flow_Ctrl_Config????????
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFcEnbaleMask;                         /* ???????????? */
    FC_CFG_CPU_STRU                     stFcCfgCpuA;                            /* A??CPU???????? */
    VOS_UINT32                          ulFcCfgMemThresholdCnt;                 /* Range:[0,8]*/
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgMem[FC_MEM_THRESHOLD_LEV_BUTT];  /* A?????????????? */
    FC_CFG_MEM_THRESHOLD_CST_STRU       stFcCfgCst;                             /* CSD???????????? */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgGprsMemSize;                     /* G?????????????????? */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgGprsMemCnt;                      /* G?????????????????? */
    FC_CFG_CPU_STRU                     stFcCfgCpuC;                            /* C??CPU???????? */
    FC_CFG_UM_UL_RATE_STRU              stFcCfgUmUlRateForCpu;                  /* C??CPU???????????????????? */
    FC_CFG_UM_UL_RATE_STRU              stFcCfgUmUlRateForTmp;                  /* C???????????????????????????? */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)    
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgCdmaMemSize;                     /* X?????????????????? */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgCdmaMemCnt;                      /* X?????????????????? */
#else
    FC_CFG_MEM_THRESHOLD_STRU           stRsv1;                     
    FC_CFG_MEM_THRESHOLD_STRU           stRsv2;                      
#endif
} FC_CFG_NV_STRU;

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __NV_STRU_GUCTTF_H__ */

