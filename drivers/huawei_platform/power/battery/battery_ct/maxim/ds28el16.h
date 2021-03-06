/*
 * ds28el16.h
 *
 * ds28el16 driver head file for battery checker
 *
 * Copyright (c) 2012-2020 Huawei Technologies Co., Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */

#ifndef _DS28EL16_H_
#define _DS28EL16_H_

#include <linux/random.h>

#include "maxim_common.h"

/* ds28el16 command lists here */
#define DS28EL16_COMMAND_START                  0x66
#define DS28EL16_WRITE_MEMORY                   0x96
#define DS28EL16_READ_MEMORY                    0x44
#define DS28EL16_READ_STATUS                    0xaa
#define DS28EL16_SET_PROTECTION                 0xc3
#define DS28EL16_GET_MAC                        0xa5
#define DS28EL16_S_SECRET                       0x3c
#define DS28EL16_RELEASE_BYTE                   0xaa
#define DS28EL16_ANON_MASK                      0xc0
#define DS28EL16_CONSTANT_BINDING               0x04

#define DS28EL16_TX_DATA_CMD_INDEX              0
#define DS28EL16_TX_DATA_PARM1_INDEX            1
#define DS28EL16_TX_DATA_PARM2_INDEX            2
#define DS28EL16_TX_DATA_PARM3_INDEX            3
#define DS28EL16_AUTH_PARAM                     2
#define DS28EL16_SEC_PARAM                      8
#define DS28EL16_S_SECRET_PAGE_PARA             0xE4
#define DS28EL16_SECRET_SEED_BYTES              32
#define DS28EL16_ROM_ID_VALID_SIGN              0x9F
#define DS28EL16_NO_PROTECTION                  0
#define DS28EL16_RD_PROTECTION                  0x01
#define DS28EL16_WR_PROTECTION                  0x02
#define DS28EL16_RW_PROTECTION                  (DS28EL16_RD_PROTECTION | DS28EL16_WR_PROTECTION)
#define DS28EL16_PROTECTION_MASK                0x03
#define DS28EL16_MASTER_PAGE_NO                 3

/* MAC input data structure */
#define DS28EL16_HMAC_PSECRET_OFFSET            0
#define DS28EL16_HMAC_ROM_ID_OFFSET             32
#define DS28EL16_HMAC_PAGE_OFFSET               40
#define DS28EL16_HMAC_CHALLENGE_OFFSET          72
#define DS28EL16_HMAC_PAGE_NO_OFFSET            104
#define DS28EL16_HMAC_MAN_ID_OFFSET             105

/* MAC types */
#define DS28EL16_CT_MAC_PAGE0                   MAC_RESOURCE_TPYE0
#define DS28EL16_CT_MAC_PAGE1                   MAC_RESOURCE_TPYE1
#define DS28EL16_MAXIM_PAGE0                    0
#define DS28EL16_MAXIM_PAGE1                    1
#define DS28EL16_MAX_USABLE_PAGE                1

#define DS28EL16_TX_BUF_LEN                     64
#define DS28EL16_RX_BUF_LEN                     64

/* communication state */
enum {
	GET_ROM_ID_INDEX = 0,
	GET_PAGE_DATA_INDEX,
	SET_PAGE_DATA_INDEX,
	GET_PAGE_STATUS_INDEX,
	SET_PAGE_STATUS_INDEX,
	SET_S_SECRET_INDEX,
	GET_MAC_INDEX,
	__MAX_COM_ERR_NUM,
};

struct ds28el16_drv_data {
	struct maxim_onewire_drv_data mdrv;
	unsigned char secret_seed[DS28EL16_SECRET_SEED_BYTES];
	unsigned char status_crc_bug;
	unsigned char s_secret_sign;
	unsigned int check_key_page_status;
};

/* for ds28el16 1page == 1block */
#define put_page_status(drv_data, id) put_block_status(drv_data, id)
#define put_one_page_status(drv_data, no, status) \
	put_one_block_status(drv_data, no, status)
#define get_page_status(drv_data) get_block_status(drv_data)
#define check_page_status_sign(drv_data) check_block_status_sign(drv_data)
#define clear_page_status_sign(drv_data) clear_block_status_sign(drv_data)

#endif /* _DS28EL16_H_ */
