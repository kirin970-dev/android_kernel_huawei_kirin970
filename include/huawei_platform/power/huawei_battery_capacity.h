/*
 * huawei_battery_capacity.h
 *
 * huawei battery capacity interface
 *
 * Copyright (c) 2019-2020 Huawei Technologies Co., Ltd.
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

#ifndef _HUAWEI_BATTERY_CAPACITY_H_
#define _HUAWEI_BATTERY_CAPACITY_H_

#include <linux/err.h>
#include <linux/power/hisi/coul/coul_drv.h>

#define HUAWEI_BATTERY "huawei-battery"

#ifdef CONFIG_HUAWEI_BATTERY_CAPACITY
int huawei_battery_capacity(void);
int huawei_battery_health(void);
#else
static inline int huawei_battery_capacity(void)
{
	return coul_drv_battery_capacity();
}

static inline int huawei_battery_health(void)
{
	return coul_drv_battery_health();
}
#endif /* CONFIG_HUAWEI_BATTERY_CAPACITY */

#endif /* _HUAWEI_BATTERY_CAPACITY_H_ */
