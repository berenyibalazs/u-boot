// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2015, 2021 Tony Dinh <mibodhi@gmail.com>
 * Copyright (C) 2015 Gerald Kerma <dreagle@doukki.net>
 */

#include <common.h>
#include <command.h>
#include <init.h>
#include <miiphy.h>
#include <net.h>
#include <asm/arch/cpu.h>
#include <asm/arch/soc.h>
#include <asm/arch/mpp.h>
#include <asm/arch/gpio.h>
#include <asm/global_data.h>
#include <asm/io.h>
#include "dns320l.h"

DECLARE_GLOBAL_DATA_PTR;

int board_early_init_f(void)
{
	/*
	 * default gpio configuration
	 * There are maximum 64 gpios controlled through 2 sets of registers
	 * the below configuration configures mainly initial LED status
	 */
	mvebu_config_gpio(DNS320L_VAL_LOW, DNS320L_VAL_HIGH,
			  DNS320L_OE_LOW, DNS320L_OE_HIGH);

	/* (all LEDs & power off active high) */
	/* Multi-Purpose Pins Functionality configuration */
	static const u32 kwmpp_config[] = {
		MPP0_NF_IO2,
		MPP1_NF_IO3,
		MPP2_NF_IO4,
		MPP3_NF_IO5,
		MPP4_NF_IO6,
		MPP5_NF_IO7,
		MPP6_SYSRST_OUTn,
		MPP7_GPO,
		MPP8_TW_SDA,
		MPP9_TW_SCK,
		MPP10_UART0_TXD,
		MPP11_UART0_RXD,
		MPP12_GPO,
		MPP13_GPIO,
		MPP14_GPIO,
		MPP15_GPIO,
		MPP16_GPIO,
		MPP17_GPIO,
		MPP18_NF_IO0,
		MPP19_NF_IO1,
		MPP20_GPIO, /* Could be MPP20_SATA1_ACTn, */
		MPP21_GPIO, /* Could be MPP21_SATA0_ACTn, */
		MPP22_GPIO,
		MPP23_GPIO,
		MPP24_GPIO,
		MPP25_GPIO,
		MPP26_GPIO,
		MPP27_GPIO,
		MPP28_GPIO,
		MPP29_GPIO,
		MPP30_GPIO,
		MPP31_GPIO,
		MPP32_GPIO,
		MPP33_GPIO,
		MPP34_GPIO,
		MPP35_GPIO,
		0
	};
	kirkwood_mpp_conf(kwmpp_config, NULL);
	return 0;
}

int board_init(void)
{
	/* address of boot parameters */
	gd->bd->bi_boot_params = mvebu_sdram_bar(0) + 0x100;

	return 0;
}

static int fdt_get_phy_addr(const char *path)
{
	const void *fdt = gd->fdt_blob;
	const u32 *reg;
	const u32 *val;
	int node, phandle, addr;

	/* Find the node by its full path */
	node = fdt_path_offset(fdt, path);
	if (node >= 0) {
		/* Look up phy-handle */
		val = fdt_getprop(fdt, node, "phy-handle", NULL);
		if (val) {
			phandle = fdt32_to_cpu(*val);
			if (!phandle)
				return -1;
			/* Follow it to its node */
			node = fdt_node_offset_by_phandle(fdt, phandle);
			if (node) {
				/* Look up reg */
				reg = fdt_getprop(fdt, node, "reg", NULL);
				if (reg) {
					addr = fdt32_to_cpu(*reg);
					return addr;
				}
			}
		}
	}
	return -1;
}

#ifdef CONFIG_RESET_PHY_R
void reset_phy(void)
{
	u16 reg;
	u16 phyaddr;
	char *name = "ethernet-controller@72000";
	char *eth0_path = "/ocp@f1000000/ethernet-controller@72000/ethernet0-port@0";

	if (miiphy_set_current_dev(name))
		return;

	phyaddr = fdt_get_phy_addr(eth0_path);
	if (phyaddr < 0)
		return;

	/* set RGMII delay */
	miiphy_write(name, phyaddr, MV88E1318_PGADR_REG, MV88E1318_MAC_CTRL_PG);
	miiphy_read(name, phyaddr, MV88E1318_MAC_CTRL_REG, &reg);
	reg |= (MV88E1318_RGMII_RX_CTRL | MV88E1318_RGMII_TX_CTRL);
	miiphy_write(name, phyaddr, MV88E1318_MAC_CTRL_REG, reg);
	miiphy_write(name, phyaddr, MV88E1318_PGADR_REG, 0);

	/* reset PHY */
	if (miiphy_reset(name, phyaddr))
		return;

	printf("MV88E1318 PHY initialized on %s\n", name);
}
#endif /* CONFIG_RESET_PHY_R */

#ifdef CONFIG_KIRKWOOD_GPIO
static int
do_sata_power_up(struct cmd_tbl *cmdtp, int flag, int argc,
		    char *const argv[])
{
	kw_gpio_set_value(24, 1);
	return 0;
}
static int
do_sata_power_down(struct cmd_tbl *cmdtp, int flag, int argc,
		    char *const argv[])
{
	kw_gpio_set_value(24, 0);
	return 0;
}
U_BOOT_CMD(sata_power_up, 1, 1, do_sata_power_up, "Enable SATA power", "");
U_BOOT_CMD(sata_power_down, 1, 1, do_sata_power_down, "Disable SATA power", "");
#endif /* CONFIG_KIRKWOOD_GPIO */
