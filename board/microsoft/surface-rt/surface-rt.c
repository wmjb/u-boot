// SPDX-License-Identifier: GPL-2.0+
/*
 *  (C) Copyright 2010-2013
 *  NVIDIA Corporation <www.nvidia.com>
 */

#include <common.h>
#include <dm.h>
#include <log.h>
#include <asm/arch/pinmux.h>
#include <asm/arch/gp_padctrl.h>
#include <asm/arch/gpio.h>
#include <asm/gpio.h>
#include <linux/delay.h>
#include "pinmux-config-surface-rt.h"
#include <i2c.h>

#define PMU_I2C_ADDRESS		0x2D
#define MAX_I2C_RETRY		3

/*
 * Routine: pinmux_init
 * Description: Do individual peripheral pinmux configs
 */
void pinmux_init(void)
{
	pinmux_config_pingrp_table(tegra3_pinmux_common,
		ARRAY_SIZE(tegra3_pinmux_common));

	pinmux_config_pingrp_table(unused_pins_lowpower,
		ARRAY_SIZE(unused_pins_lowpower));

	/* Initialize any non-default pad configs (APB_MISC_GP regs) */
	pinmux_config_drvgrp_table(cardhu_padctrl, ARRAY_SIZE(cardhu_padctrl));
}

#if defined(CONFIG_MMC_SDHCI_TEGRA)
/*
 * Do I2C/PMU writes to bring up SD card bus power
 *
 */
 void gpio_early_init_uart(void)
{
	gpio_request(TEGRA_GPIO(X, 6), "Force OFF# X13");
	gpio_direction_output(TEGRA_GPIO(X, 6), 1);
	gpio_request(TEGRA_GPIO(X, 7), "Force OFF# X14");
	gpio_direction_output(TEGRA_GPIO(X, 7), 1);
}

/*
 * Enable AX88772B USB to LAN controller
 */
void pin_mux_usb(void)



{

	gpio_request(TEGRA_GPIO(D, 4), "MRVL-SD8797_Wifi_Enable");
	gpio_direction_output(TEGRA_GPIO(D, 4), 0);
	udelay(5);
	gpio_set_value(TEGRA_GPIO(D, 4), 1);
	printf("Enabled MRVL-SD8797 WiFi GPIO D4\n");
	
	gpio_request(TEGRA_GPIO(D, 1), "MRVL-SD8797_BT_Enable");
	gpio_direction_output(TEGRA_GPIO(D, 1), 0);
	udelay(5);
	gpio_set_value(TEGRA_GPIO(D, 1), 1);
	printf("Enabled MRVL-SD8797 BT GPIO D1\n");
	
        puts("Display Panel Regulator enabled\n");
	gpio_request(TEGRA_GPIO(B, 2), "panel_&_EC_enabled");
	gpio_direction_output(TEGRA_GPIO(B, 2), 0);
	udelay(5);
	gpio_set_value(TEGRA_GPIO(B, 2), 1);	
	 puts("Display Panel & EC enabled\n");
	
	
	gpio_request(TEGRA_GPIO(DD, 0), "backlight_enable");
	gpio_direction_output(TEGRA_GPIO(DD, 0), 0);
	udelay(5);
	gpio_set_value(TEGRA_GPIO(DD, 0), 1);
	 puts("Backlight enabled\n");
	 
	gpio_request(TEGRA_GPIO(DD, 2), "panel_regulator_enable");
	gpio_direction_output(TEGRA_GPIO(DD, 2), 0);
	udelay(5);
	gpio_set_value(TEGRA_GPIO(DD, 2), 1);
	 puts("panel_regulator_enable\n");

	gpio_request(TEGRA_GPIO(DD, 6), "usb1_regulator_enable");
	gpio_direction_output(TEGRA_GPIO(DD, 6), 0);
	udelay(5);
	gpio_set_value(TEGRA_GPIO(DD, 6), 1);
	 puts("usb1_regulator_enable\n");
	
	gpio_request(TEGRA_GPIO(N, 7), "host1x_enable");
	gpio_direction_output(TEGRA_GPIO(N, 7), 0);
	udelay(5);
	gpio_set_value(TEGRA_GPIO(N, 7), 0);
	 puts("host1x enable\n");
}

/*
 * Backlight off before OS handover
 */
void board_preboot_os(void)
{
	gpio_request(TEGRA_GPIO(V, 2), "BL_ON");
	gpio_direction_output(TEGRA_GPIO(V, 2), 0);
}
 
void board_sdmmc_voltage_init(void)
{
	struct udevice *dev;
	uchar reg, data_buffer[1];
	int ret;
	int i;

	ret = i2c_get_chip_for_busnum(0, PMU_I2C_ADDRESS, 1, &dev);
	if (ret) {
		debug("%s: Cannot find PMIC I2C chip\n", __func__);
		return;
	}

	/* TPS659110: LDO5_REG = 3.3v, ACTIVE to SDMMC1 */
	data_buffer[0] = 0x65;
	reg = 0x32;

	for (i = 0; i < MAX_I2C_RETRY; ++i) {
		if (dm_i2c_write(dev, reg, data_buffer, 1))
			udelay(100);
	}
}

/*
 * Routine: pin_mux_mmc
 * Description: setup the MMC muxes, power rails, etc.
 */
void pin_mux_mmc(void)
{
	/*
	 * NOTE: We don't do mmc-specific pin muxes here.
	 * They were done globally in pinmux_init().
	 */

	/* Bring up the SDIO1 power rail */
	board_sdmmc_voltage_init();
}
#endif	/* MMC */
