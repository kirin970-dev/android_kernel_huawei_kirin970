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

/*****************************************************************************
  1 ??????????
*****************************************************************************/
#include "RnicCtx.h"
#include "RnicEntity.h"
#include "PsCommonDef.h"
#include "AtRnicInterface.h"
#include "RnicProcMsg.h"
#include "RnicDemandDialFileIO.h"
#include "RnicLog.h"
#include "RnicDebug.h"




/*****************************************************************************
    ??????????????????????.C??????????
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_CTX_C


/*****************************************************************************
  2 ????????????
*****************************************************************************/

/* RNIC CTX,????????RNIC?????????? */
RNIC_CTX_STRU                           g_stRnicCtx;

extern RNIC_STATS_INFO_STRU                    g_astRnicStats[RNIC_NET_ID_MAX_NUM];



VOS_VOID RNIC_InitCtx(
    RNIC_CTX_STRU                      *pstRnicCtx
)
{
    VOS_UINT8                           ucIndex;

    TAF_MEM_SET_S(g_astRnicStats, sizeof(g_astRnicStats), 0x00, sizeof(g_astRnicStats));

#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)
    /* ??????RNIC??????????Linux??????????API???????? */
    RNIC_InitRnicNetInterfaceCfg(pstRnicCtx);
#endif

    RNIC_InitUsbTetherInfo();

    for (ucIndex = 0 ; ucIndex < RNIC_NET_ID_MAX_NUM ; ucIndex++)
    {
        /* ??????RNIC???????? */
        RNIC_ClearNetDsFlowStats(ucIndex);

        /* ??????RNIC PDP?????? */
        RNIC_InitPdpCtx(&(pstRnicCtx->astSpecCtx[ucIndex].stPdpCtx), ucIndex);

        /* ?????????????? */
        pstRnicCtx->astSpecCtx[ucIndex].enFlowCtrlStatus = RNIC_FLOW_CTRL_STATUS_STOP;

        /* ??????????ID */
        /* ????????????????????????????????????????MODEM */
        pstRnicCtx->astSpecCtx[ucIndex].enModemId        = RNIC_GET_MODEM_ID_BY_NET_ID(ucIndex);

        pstRnicCtx->astSpecCtx[ucIndex].enRmNetId        = ucIndex;
        pstRnicCtx->astSpecCtx[ucIndex].lSpePort         = RNIC_INVALID_SPE_PORT;
        pstRnicCtx->astSpecCtx[ucIndex].ulIpfPortFlg     = VOS_FALSE;

        pstRnicCtx->astSpecCtx[ucIndex].enRatType        = IMSA_RNIC_IMS_RAT_TYPE_BUTT;

#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)
        if (VOS_NULL_PTR != pstRnicCtx->astSpecCtx[ucIndex].pstPriv)
        {
            pstRnicCtx->astSpecCtx[ucIndex].pstPriv->stNapi.weight = RNIC_GET_NAPI_WEIGHT();
        }

        /* ??????RNIC????Poll???????? */
        IMM_ZcQueueHeadInit(RNIC_GET_PollBuff_QUE(ucIndex));

        pstRnicCtx->astSpecCtx[ucIndex].enNapiRcvIf      = RNIC_NAPI_GRO_RCV_IF;
#endif
    }

    /* ??????RNIC???????????? */
    RNIC_InitAllTimers(pstRnicCtx->astTimerCtx);

    /* ?????????????????? */
    RNIC_InitDialMode(&(pstRnicCtx->stDialMode));

    /* ???????????????????????????????????? */
    RNIC_ClearTiDialDownExpCount();

    RNIC_SetTimer4WakeFlg(VOS_FALSE);

    /* ???????????????? */
    RNIC_InitResetSem();

    /* ??????IPF???????? */
    RNIC_InitIpfMode(pstRnicCtx);

    return;
}


VOS_VOID RNIC_InitPdpCtx(
    RNIC_PDP_CTX_STRU                  *pstPdpCtx,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_InitIpv4PdpCtx(&(pstPdpCtx->stIpv4PdpInfo));
    RNIC_InitIpv6PdpCtx(&(pstPdpCtx->stIpv6PdpInfo));
    RNIC_InitIpv4v6PdpCtx(&(pstPdpCtx->stIpv4v6PdpInfo), ucRmNetId);

    IMM_ZcQueueHeadInit(&pstPdpCtx->stImsQue);

    return;
}


VOS_VOID RNIC_ResetDialMode(
    RNIC_DIAL_MODE_STRU                *pstDialMode
)
{
    pstDialMode->enDialMode             = RNIC_DIAL_MODE_MANUAL;
    pstDialMode->ulIdleTime             = RNIC_DIAL_DEMA_IDLE_TIME;
    pstDialMode->enEventReportFlag      = RNIC_FORBID_EVENT_REPORT;

    return;
}


VOS_VOID RNIC_InitDialMode(
    RNIC_DIAL_MODE_STRU                *pstDialMode
)
{
    VOS_UINT32                          ulRlst;

    pstDialMode->enDialMode             = RNIC_DIAL_MODE_MANUAL;
    pstDialMode->ulIdleTime             = RNIC_DIAL_DEMA_IDLE_TIME;
    pstDialMode->enEventReportFlag      = RNIC_FORBID_EVENT_REPORT;

    ulRlst                              = RNIC_InitDemandDialFile();

    if ( VOS_ERR == ulRlst)
    {
       RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialMode:RNIC_InitDemandDialFile ERR!");
    }

    return;
}


VOS_VOID RNIC_InitIpv4PdpCtx(
    RNIC_IPV4_PDP_INFO_STRU            *pstIpv4PdpCtx
)
{
    pstIpv4PdpCtx->enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* Modified by l60609 for L-C??????????, 2014-1-14, begin */
    pstIpv4PdpCtx->ucRabId     = RNIC_RAB_ID_INVALID;
    /* Modified by l60609 for L-C??????????, 2014-1-14, end */
    pstIpv4PdpCtx->ulIpv4Addr  = 0;


    return;
}


VOS_VOID RNIC_InitIpv6PdpCtx(
    RNIC_IPV6_PDP_INFO_STRU            *pstIpv6PdpCtx
)
{
    pstIpv6PdpCtx->enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* Modified by l60609 for L-C??????????, 2014-1-14, begin */
    pstIpv6PdpCtx->ucRabId     = RNIC_RAB_ID_INVALID;
    /* Modified by l60609 for L-C??????????, 2014-1-14, end */

    TAF_MEM_SET_S(pstIpv6PdpCtx->aucIpv6Addr,
               sizeof(pstIpv6PdpCtx->aucIpv6Addr),
               0x00,
               RNIC_MAX_IPV6_ADDR_LEN);


    return;
}


VOS_VOID RNIC_InitIpv4v6PdpCtx(
    RNIC_IPV4V6_PDP_INFO_STRU          *pstIpv4v6PdpCtx,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* ????PDP?????????? */
    pstPdpAddr                              = RNIC_GetPdpCtxAddr(ucRmNetId);

    /* Modified by l60609 for L-C??????????, 2014-1-14, begin */
    pstIpv4v6PdpCtx->enRegStatus            = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstIpv4v6PdpCtx->ucRabId                = RNIC_RAB_ID_INVALID;
    /* Modified by l60609 for L-C??????????, 2014-1-14, end */

    pstPdpAddr->stIpv4PdpInfo.ucRabId       = RNIC_RAB_ID_INVALID;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = RNIC_RAB_ID_INVALID;

    pstIpv4v6PdpCtx->ulIpv4Addr             = 0;

    TAF_MEM_SET_S(pstIpv4v6PdpCtx->aucIpv6Addr,
               sizeof(pstIpv4v6PdpCtx->aucIpv6Addr),
               0x00,
               RNIC_MAX_IPV6_ADDR_LEN);


}


VOS_VOID RNIC_InitResetSem(VOS_VOID)
{
    g_stRnicCtx.hResetSem  = VOS_NULL_PTR;

    /* ???????????????? */
    if (VOS_OK != VOS_SmBCreate( "RNIC", 0, VOS_SEMA4_FIFO, &g_stRnicCtx.hResetSem))
    {
        PS_PRINTF("Create rnic acpu cnf sem failed!\r\n");
        RNIC_DBG_SET_SEM_INIT_FLAG(VOS_FALSE);
        RNIC_DBG_CREATE_BINARY_SEM_FAIL_NUM(1);

        return;
    }
    else
    {
        RNIC_DBG_SAVE_BINARY_SEM_ID(g_stRnicCtx.hResetSem);
    }

    RNIC_DBG_SET_SEM_INIT_FLAG(VOS_TRUE);

    return;
}


VOS_VOID RNIC_InitIpfMode(
    RNIC_CTX_STRU                      *pstRnicCtx
)
{
    TAF_NV_ADS_IPF_MODE_CFG_STRU        stIpfMode;

    TAF_MEM_SET_S(&stIpfMode, (VOS_SIZE_T)sizeof(stIpfMode), 0x00, (VOS_SIZE_T)sizeof(TAF_NV_ADS_IPF_MODE_CFG_STRU));

    pstRnicCtx->ucIpfMode = 0;

    /* ????NV?? */
    if (NV_OK == TAF_ACORE_NV_READ(MODEM_ID_0,
                                   en_NV_Item_ADS_IPF_MODE_CFG,
                                   &stIpfMode,
                                   (VOS_UINT32)sizeof(TAF_NV_ADS_IPF_MODE_CFG_STRU)))
    {
        pstRnicCtx->ucIpfMode = stIpfMode.ucIpfMode;
    }

    return;
}

#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)

VOS_VOID RNIC_CheckNetIfCfgValid(
    RNIC_CTX_STRU                      *pstRnicCtx
)
{
    if (pstRnicCtx->stRnicNetIfCfg.ucNetInterfaceMode >= RNIC_NET_IF_BUTT)
    {
        pstRnicCtx->stRnicNetIfCfg.ucNetInterfaceMode = RNIC_NET_IF_NETRX;
    }

    if ((pstRnicCtx->stRnicNetIfCfg.ucNapiPollWeight > RNIC_NAPI_POLL_MAX_WEIGHT) ||
        (0 == pstRnicCtx->stRnicNetIfCfg.ucNapiPollWeight))
    {
        pstRnicCtx->stRnicNetIfCfg.ucNapiPollWeight   = RNIC_NAPI_POLL_DEFAULT_WEIGHT;
    }

    if ((pstRnicCtx->stRnicNetIfCfg.usNapiPollQueMaxLen > RNIC_POLL_QUEUE_DEFAULT_MAX_LEN) ||
        (0 == pstRnicCtx->stRnicNetIfCfg.usNapiPollQueMaxLen))
    {
        pstRnicCtx->stRnicNetIfCfg.usNapiPollQueMaxLen   = RNIC_POLL_QUEUE_DEFAULT_MAX_LEN;
    }

    if (pstRnicCtx->stRnicNetIfCfg.enNapiWeightAdjMode >= NAPI_WEIGHT_ADJ_MODE_BUTT)
    {
        pstRnicCtx->stRnicNetIfCfg.enNapiWeightAdjMode = NAPI_WEIGHT_ADJ_STATIC_MODE;
    }

    return;
}

VOS_VOID RNIC_InitRnicNetInterfaceCfg(
    RNIC_CTX_STRU                      *pstRnicCtx
)
{
    TAF_NV_RNIC_NET_IF_CFG_STRU        stRnicNetIfCfg;

    TAF_MEM_SET_S(&stRnicNetIfCfg, (VOS_SIZE_T)sizeof(stRnicNetIfCfg), 0x00, (VOS_SIZE_T)sizeof(TAF_NV_RNIC_NET_IF_CFG_STRU));

    /* ????NV?? */
    if (NV_OK == TAF_ACORE_NV_READ(MODEM_ID_0,
                                   en_NV_Item_Rnic_Net_If_Cfg,
                                   &stRnicNetIfCfg,
                                   (VOS_UINT32)sizeof(TAF_NV_RNIC_NET_IF_CFG_STRU)))
    {
        pstRnicCtx->stRnicNetIfCfg.ucNetInterfaceMode  = stRnicNetIfCfg.ucNetInterfaceMode;
        pstRnicCtx->stRnicNetIfCfg.enNapiWeightAdjMode = stRnicNetIfCfg.enNapiWeightAdjMode;
        pstRnicCtx->stRnicNetIfCfg.ucNapiPollWeight    = stRnicNetIfCfg.ucNapiPollWeight;
        pstRnicCtx->stRnicNetIfCfg.usNapiPollQueMaxLen = stRnicNetIfCfg.usNapiPollQueMaxLen;

        pstRnicCtx->stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stDlPktNumPerSecLevel.ulDlPktNumPerSecLevel1
                  = stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stDlPktNumPerSecLevel.ulDlPktNumPerSecLevel1;
        pstRnicCtx->stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stDlPktNumPerSecLevel.ulDlPktNumPerSecLevel2
                  = stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stDlPktNumPerSecLevel.ulDlPktNumPerSecLevel2;
        pstRnicCtx->stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stDlPktNumPerSecLevel.ulDlPktNumPerSecLevel3
                  = stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stDlPktNumPerSecLevel.ulDlPktNumPerSecLevel3;
        pstRnicCtx->stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stDlPktNumPerSecLevel.ulDlPktNumPerSecLevel4
                  = stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stDlPktNumPerSecLevel.ulDlPktNumPerSecLevel4;

        pstRnicCtx->stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stNapiWeightLevel.ucNapiWeightLevel1
                  = stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stNapiWeightLevel.ucNapiWeightLevel1;
        pstRnicCtx->stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stNapiWeightLevel.ucNapiWeightLevel2
                  = stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stNapiWeightLevel.ucNapiWeightLevel2;
        pstRnicCtx->stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stNapiWeightLevel.ucNapiWeightLevel3
                  = stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stNapiWeightLevel.ucNapiWeightLevel3;
        pstRnicCtx->stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stNapiWeightLevel.ucNapiWeightLevel4
                  = stRnicNetIfCfg.stNapiWeightDynamicAdjCfg.stNapiWeightLevel.ucNapiWeightLevel4;

    }
    else
    {
        pstRnicCtx->stRnicNetIfCfg.ucNetInterfaceMode     = RNIC_NET_IF_NETRX;
        pstRnicCtx->stRnicNetIfCfg.enNapiWeightAdjMode    = NAPI_WEIGHT_ADJ_STATIC_MODE;
        pstRnicCtx->stRnicNetIfCfg.ucNapiPollWeight       = RNIC_NAPI_POLL_DEFAULT_WEIGHT;
        pstRnicCtx->stRnicNetIfCfg.usNapiPollQueMaxLen    = RNIC_POLL_QUEUE_DEFAULT_MAX_LEN;
    }

    RNIC_CheckNetIfCfgValid(pstRnicCtx);

    return;
}
#endif


VOS_VOID RNIC_InitUsbTetherInfo(VOS_VOID)
{
    TAF_MEM_SET_S(g_stRnicCtx.stUsbTetherInfo.aucRmnetName, RNIC_RMNET_NAME_MAX_LEN, 0x00, RNIC_RMNET_NAME_MAX_LEN);

    g_stRnicCtx.stUsbTetherInfo.enTetherConnStat    = AT_RNIC_USB_TETHER_DISCONNECT;
    g_stRnicCtx.stUsbTetherInfo.ucMatchRmnetNameFlg = VOS_FALSE;

    return;
}


VOS_VOID RNIC_ClearNetDsFlowStats(RNIC_RMNET_ID_ENUM_UINT8 enRmNetId)
{
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;

    pstNetCntxt = RNIC_GET_SPEC_NET_CTX(enRmNetId);

    pstNetCntxt->stDsFlowStats.ulCurrentRecvRate   = 0;
    pstNetCntxt->stDsFlowStats.ulPeriodRecvPktNum  = 0;
    pstNetCntxt->stDsFlowStats.ulTotalRecvFluxLow  = 0;
    pstNetCntxt->stDsFlowStats.ulTotalRecvFluxHigh = 0;

    pstNetCntxt->stDsFlowStats.ulCurrentSendRate   = 0;
    pstNetCntxt->stDsFlowStats.ulPeriodSendPktNum  = 0;
    pstNetCntxt->stDsFlowStats.ulTotalSendFluxLow  = 0;
    pstNetCntxt->stDsFlowStats.ulTotalSendFluxHigh = 0;

    return;
}


RNIC_CTX_STRU* RNIC_GetRnicCtxAddr(VOS_VOID)
{
    return &(g_stRnicCtx);
}


VOS_UINT32 RNIC_GetTiDialDownExpCount( VOS_VOID)
{
    return (g_stRnicCtx.ulTiDialDownExpCount);
}



VOS_VOID RNIC_IncTiDialDownExpCount( VOS_VOID)
{
    (g_stRnicCtx.ulTiDialDownExpCount)++;

    return;
}


VOS_VOID RNIC_ClearTiDialDownExpCount( VOS_VOID)
{
    g_stRnicCtx.ulTiDialDownExpCount = 0;

    return;
}


VOS_UINT32 RNIC_GetCurrentUlRate(VOS_UINT8 ucRmNetId)
{
    return (g_stRnicCtx.astSpecCtx[ucRmNetId].stDsFlowStats.ulCurrentSendRate);
}


VOS_VOID RNIC_SetCurrentUlRate(
    VOS_UINT32                          ulULDataRate,
    VOS_UINT8                           ucRmNetId
)
{
    g_stRnicCtx.astSpecCtx[ucRmNetId].stDsFlowStats.ulCurrentSendRate = ulULDataRate;

    return;
}



VOS_UINT32 RNIC_GetCurrentDlRate(VOS_UINT8 ucRmNetId)
{
    return (g_stRnicCtx.astSpecCtx[ucRmNetId].stDsFlowStats.ulCurrentRecvRate);
}


VOS_VOID RNIC_SetCurrentDlRate(
    VOS_UINT32                          ulDLDataRate,
    VOS_UINT8                           ucRmNetId
)
{
    g_stRnicCtx.astSpecCtx[ucRmNetId].stDsFlowStats.ulCurrentRecvRate = ulDLDataRate;

    return;
}


RNIC_DIAL_MODE_STRU* RNIC_GetDialModeAddr(VOS_VOID)
{
    return &(g_stRnicCtx.stDialMode);
}


RNIC_PDP_CTX_STRU* RNIC_GetPdpCtxAddr(VOS_UINT8 ucRmNetId)
{
    return &(g_stRnicCtx.astSpecCtx[ucRmNetId].stPdpCtx);
}


RNIC_TIMER_CTX_STRU*  RNIC_GetTimerAddr( VOS_VOID )
{
    return g_stRnicCtx.astTimerCtx;
}


VOS_UINT32 RNIC_GetTimer4WakeFlg(VOS_VOID)
{
    return g_stRnicCtx.ulSetTimer4WakeFlg;
}


VOS_VOID RNIC_SetTimer4WakeFlg(VOS_UINT32 ulFlg)
{
    g_stRnicCtx.ulSetTimer4WakeFlg = ulFlg;
}


RNIC_SPEC_CTX_STRU *RNIC_GetSpecNetCardCtxAddr(VOS_UINT8 ucRmNetId)
{
    return &(g_stRnicCtx.astSpecCtx[ucRmNetId]);
}


RNIC_SPEC_CTX_STRU* RNIC_GetNetCntxtByRmNetId(RNIC_RMNET_ID_ENUM_UINT8 enRmNetId)
{
    if (enRmNetId >= RNIC_RMNET_ID_BUTT)
    {
        return VOS_NULL_PTR;
    }

    return RNIC_GET_SPEC_NET_CTX(enRmNetId);
}



VOS_SEM RNIC_GetResetSem(VOS_VOID)
{
    return g_stRnicCtx.hResetSem;
}

#if (FEATURE_ON == FEATURE_RNIC_NAPI_GRO)

VOS_UINT32 RNIC_UpdateRmnetNapiRcvIfByName(VOS_INT32 ulRmNetId)
{
    VOS_UINT32                          ulRet = VOS_FALSE;

    if (0 == VOS_StrNiCmp(g_stRnicCtx.stUsbTetherInfo.aucRmnetName, RNIC_GET_SPEC_NET_DEV_NAME(ulRmNetId),RNIC_RMNET_NAME_MAX_LEN))
    {
        if (AT_RNIC_USB_TETHER_CONNECTED == g_stRnicCtx.stUsbTetherInfo.enTetherConnStat)
        {
            RNIC_GET_NAPI_RCV_IF(ulRmNetId) = RNIC_NAPI_NETIF_RCV_IF;
        }
        else
        {
            RNIC_GET_NAPI_RCV_IF(ulRmNetId) = RNIC_NAPI_GRO_RCV_IF;
        }

        g_stRnicCtx.stUsbTetherInfo.ucMatchRmnetNameFlg = VOS_TRUE;
        ulRet = VOS_TRUE;
    }
    else
    {
        g_stRnicCtx.stUsbTetherInfo.ucMatchRmnetNameFlg = VOS_FALSE;
    }

    return ulRet;
}


VOS_VOID RNIC_UpdateIpv6RmnetNapiRcvIfDefault(VOS_INT32 ulRmNetId)
{
    /*
     * ????USB Tethering????????????????????????????rmnet??????,
     * ????IPv6??Rmnet????????????????????????????netif_receive_skb??
     * ??????????napi_gro_receive??
     */
    if ((AT_RNIC_USB_TETHER_CONNECTED == g_stRnicCtx.stUsbTetherInfo.enTetherConnStat)
     && (VOS_FALSE                    == g_stRnicCtx.stUsbTetherInfo.ucMatchRmnetNameFlg)
     && (RNIC_PDP_REG_STATUS_ACTIVE   == RNIC_GET_SPEC_NET_IPV6_REG_STATE(ulRmNetId))
     && (RNIC_PDP_REG_STATUS_ACTIVE   != RNIC_GET_SPEC_NET_IPV4_REG_STATE(ulRmNetId)))
    {
        RNIC_GET_NAPI_RCV_IF(ulRmNetId) = RNIC_NAPI_NETIF_RCV_IF;
    }
    else
    {
        RNIC_GET_NAPI_RCV_IF(ulRmNetId) = RNIC_NAPI_GRO_RCV_IF;
    }

    return;
}
#endif

