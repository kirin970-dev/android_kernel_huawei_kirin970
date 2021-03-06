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

#ifndef __RNIC_MNTN_H__
#define __RNIC_MNTN_H__

/*****************************************************************************
  1 ??????????????
*****************************************************************************/
#include "vos.h"
#include "TafDiagComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ??????
*****************************************************************************/
#define RNIC_MNTN_COMM_MOUDLE_ID         (DIAG_GEN_MODULE(MODEM_ID_0, DIAG_MODE_COMM))

/*****************************************************************************
  3 ????????
*****************************************************************************/


/*****************************************************************************
  4 ????????????
*****************************************************************************/


/*****************************************************************************
  5 ??????????
*****************************************************************************/


/*****************************************************************************
  6 ????????
*****************************************************************************/


/*****************************************************************************
  7 STRUCT????
*****************************************************************************/

/*****************************************************************************
 ????????  : RNIC_MNTN_COMM_HEADER_STRU
 ????????  : RNIC??????????????????
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucVer;
    VOS_UINT8                           ucReserved;

    VOS_UINT16                          usReserved0;
    VOS_UINT16                          usReserved1;
    VOS_UINT16                          usReserved2;

} RNIC_MNTN_COMM_HEADER_STRU;

/*****************************************************************************
 ????????  : RNIC_MNTN_UL_PKT_STATS_STRU
 ????????  : ????????????????????????
*****************************************************************************/
typedef struct
{
    RNIC_MNTN_COMM_HEADER_STRU          stCommHeader;

    VOS_UINT8                           ucRmNetId;
    VOS_UINT8                           aucReserved0;
    VOS_UINT8                           aucReserved1;
    VOS_UINT8                           aucReserved2;
    VOS_UINT32                          ulUlRecvIpv4PktNum;                     /* RNIC????????IPV4?????????? */
    VOS_UINT32                          ulUlRecvIpv6PktNum;                     /* RNIC????????IPV6?????????? */
    VOS_UINT32                          ulUlRecvIpv4v6PktNum;                   /* IPV4V6??????????RNIC??????????????????(IPV4??IPV6) */
    VOS_UINT32                          ulUlRecvUndiaPktNum;                    /* RNIC?????????????????????????? */
    VOS_UINT32                          ulUlSendPktNum;                         /* RNIC??????????ADS?????????? */
    VOS_UINT32                          ulUlSendPktFailNum;                     /* RNIC??ADS?????????????????????? */
    VOS_UINT32                          ulUlIpv4BrdcstPktNum;                   /* RNIC??????????????????IPV4???????????? */
    VOS_UINT32                          ulUlImmzcFailPktNum;                    /* RNIC??????????IMM_ZC?????????? */
    VOS_UINT32                          ulUlRmvMacHdrFailPktNum;                /* RNIC????????MAC???????????? */
    VOS_UINT32                          ulUlNetCardDiscardNum;                  /* RNIC???????????????????????????????????? */
    VOS_UINT32                          ulUlFlowCtrlDiscardNum;                 /* RNIC???????????????????????????? */
    VOS_UINT32                          ulUlRecvErrPktNum;                      /* RNIC????????????????????(??ipv4??ipv6??) */
    VOS_UINT32                          ulUlSendAppDialUpSucc;                  /* RNIC????????APP???????? */
    VOS_UINT32                          ulUlSendAppDialUpFail;                  /* RNIC????APP???????????? */
    VOS_UINT32                          ulUlSendAppDialDownSucc;                /* RNIC????????APP???????? */
    VOS_UINT32                          ulUlSendAppDialDownFail;                /* RNIC????APP???????????? */
    VOS_UINT32                          ulUlRabIdErr;                           /* Rab id???? */
    VOS_UINT32                          ulUlNetIdDiscardNum;                    /* RNIC????ID???????????????????????? */
    VOS_UINT32                          ulUlModemIdDiscardNum;                  /* RNIC Modem ID???????????????????????? */

} RNIC_MNTN_UL_PKT_STATS_STRU;

/*****************************************************************************
 ????????  : RNIC_MNTN_DL_PKT_STATS_STRU
 ????????  : ????????????????????????
*****************************************************************************/
typedef struct
{
    RNIC_MNTN_COMM_HEADER_STRU          stCommHeader;

    VOS_UINT8                           ucRmNetId;
    VOS_UINT8                           aucReserved0;
    VOS_UINT8                           aucReserved1;
    VOS_UINT8                           aucReserved2;
    VOS_UINT32                          ulDlRecvIpv4PktNum;                     /* RNIC????????IPV4?????????? */
    VOS_UINT32                          ulDlRecvIpv6PktNum;                     /* RNIC????????IPV6?????????? */
    VOS_UINT32                          ulDlSendPktNum;                         /* RNIC?????????????????? */
    VOS_UINT32                          ulDlSendPktFailNum;                     /* RNIC?????????????????????? */
    VOS_UINT32                          ulDlRecvBigPktNum;                      /* RNIC??????????????????MTU?????? */
    VOS_UINT32                          ulDlDiscardPktNum;                      /* RNIC???????????????????????? */
    VOS_UINT32                          ulDlAddMacHdFailNum;                    /* RNIC??????MAC???????????? */
    VOS_UINT32                          ulDlNetCardDiscardNum;                  /* RNIC???????????????????????????????????? */
    VOS_UINT32                          ulDlRecvErrPktNum;                      /* RNIC????????????????????(??ipv4??ipv6??) */
    VOS_UINT32                          ulDlNetIdDiscardNum;                    /* RNIC????ID???????????????????????? */

    VOS_UINT32                          ulDlNapiPollQueDiscardPktNum;           /* RNIC??????????????NAPI Poll buffer?????????????????????????????????????? */
    VOS_UINT32                          ulDlNapiWeight;                         /* RNIC????????NAPI Weight?? */
    VOS_UINT32                          ulDlNapiRecvPktNum;                     /* RNIC????????NAPI???????????????? */

} RNIC_MNTN_DL_PKT_STATS_STRU;


/*****************************************************************************
  8 UNION????
*****************************************************************************/


/*****************************************************************************
  9 OTHERS????
*****************************************************************************/


/*****************************************************************************
  10 ????????
*****************************************************************************/
VOS_VOID RNIC_MNTN_TransReport(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLen
);
VOS_VOID RNIC_MNTN_ReportAllStatsInfo(VOS_UINT8 ucRmNetId);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of RnicMntn.h */
