/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2010-2012, NVIDIA CORPORATION.  All rights reserved.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

#include "tegra30-common.h"

/* VDD core PMIC */
#define CONFIG_TEGRA_VDD_CORE_TPS62361B_SET3

/* High-level configuration options */
#define CONFIG_TEGRA_BOARD_STRING	"Microsoft Surface RT"

#define BOARD_EXTRA_ENV_SETTINGS \
	"kernel_addr_r=0x80008000\0" \
	"dtb_addr_r=0x83000000\0" \
	"ramdisk_addr_r=0x84000000\0" \
	"script_addr_r=0x87000000\0" \
	"kernel_file=zImage\0" \
	"dtb_file=tegra30-microsoft-surface-rt.dtb\0" \
	"ramdisk_file=initramfs\0" \
	"bootkernel=bootz ${kernel_addr_r} - ${dtb_addr_r}\0" \
	"bootrdkernel=bootz ${kernel_addr_r} ${ramdisk_addr_r} ${dtb_addr_r}\0" \
	"bootmenu_0=boot Linux=run bootz\0" \
	"bootmenu_1=boot LNX=run boot_lnx\0" \
	"bootmenu_2=boot SOS=run boot_sos\0" \
	"bootmenu_3=fastboot=fastboot usb 0\0" \
	"bootmenu_delay=-1\0"

/* Board-specific serial config */
#define CONFIG_TEGRA_ENABLE_UARTA
#define CONFIG_SYS_NS16550_COM1		NV_PA_APB_UARTA_BASE

#define CONFIG_MACH_TYPE		MACH_TYPE_CARDHU

#include "tegra-common-post.h"

#endif /* __CONFIG_H */
