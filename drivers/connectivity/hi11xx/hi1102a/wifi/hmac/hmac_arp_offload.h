

#ifndef __HMAC_ARP_OFFLOAD_H__
#define __HMAC_ARP_OFFLOAD_H__

/* 1 其他头文件包含 */
#include "oal_ext_if.h"
#include "mac_vap.h"
#include "dmac_ext_if.h"
#include "hmac_vap.h"
#include "hmac_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#undef THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ARP_OFFLOAD_H

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
/* 2 宏定义 */
/* 3 枚举定义 */
/* 4 全局变量声明 */
/* 5 消息头定义 */
/* 6 消息定义 */
/* 7 STRUCT定义 */
/* 8 UNION定义 */
/* 9 OTHERS定义 */
/* 10 函数声明 */
extern oal_uint32 hmac_arp_offload_set_ip_addr(mac_vap_stru *pst_mac_vap,
                                               dmac_ip_type_enum_uint8 en_type,
                                               dmac_ip_oper_enum_uint8 en_oper,
                                               oal_void *pst_ip_addr,
                                               oal_void *pst_mask_addr);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of hmac_arp_offload.h */
