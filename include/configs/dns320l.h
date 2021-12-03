/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2015, 2021 Tony Dinh <mibodhi@gmail.com>
 * Copyright (C) 2015
 * Gerald Kerma <dreagle@doukki.net>
 * Luka Perkov <luka.perkov@sartura.hr>
 */

#ifndef _CONFIG_DNS320L_H
#define _CONFIG_DNS320L_H

/* high level configuration options */
#define CONFIG_FEROCEON_88FR131	1	/* CPU Core subversion */
#define CONFIG_KW88F6192		1	/* SOC Name */
#define CONFIG_KW88F6702		1	/* SOC Name */
#define CONFIG_KIRKWOOD_GPIO 	1

#include "mv-common.h"

/* environment variables configuration */

/* default environment variables */
#define CONFIG_BOOTCOMMAND \
	"setenv bootargs ${console} ${mtdparts} ${bootargs_root}; " \
	"ubi part ubi; " \
	"ubi read ${loadaddr} kernel; "  \
	"bootm ${loadaddr}"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"console=console=ttyS0,115200\0" \
	"mtdids="CONFIG_MTDIDS_DEFAULT "\0" \
	"mtdparts="CONFIG_MTDPARTS_DEFAULT "\0" \
	"bootargs_root=\0"

/* Ethernet driver configuration */
#ifdef CONFIG_CMD_NET
#define CONFIG_MVGBE_PORTS	{1, 0}	/* enable port 0 only */
#define CONFIG_PHY_BASE_ADR	1
#define CONFIG_RESET_PHY_R
#endif /* CONFIG_CMD_NET */

/* SATA driver configuration */
#ifdef CONFIG_SATA
#define CONFIG_SYS_SATA_MAX_DEVICE	2
#define CONFIG_LBA48
#endif /* CONFIG_SATA */

/* RTC driver configuration */
#ifdef CONFIG_CMD_DATE /* FIXME */
#define CONFIG_RTC_MV /* FIXME */
#endif /* CONFIG_CMD_DATE */

#endif /* _CONFIG_NSA310S_H */
