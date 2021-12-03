/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2015
 * Gerald Kerma <dreagle@doukki.net>
 * Tony Dinh <mibodhi@gmail.com>
 */

#ifndef __DNS320L_H
#define __DNS320L_H

/* low GPIO's */
#define HDD2_ORAGE_LED	    (1 << 22)
#define HDD1_ORAGE_LED	    (1 << 23)
#define SATA_POWER   	    (1 << 24)
#define USB_BLUE_LED	    (1 << 25)
#define USB_ORANGE_LED	    (1 << 26)
#define USB_EJECT_BTN       (1 << 27)
#define RESET_BTN           (1 << 28)
/* #define POWER_BTN           (1 << 29) */

#define DNS320L_OE_LOW		(~(SATA_POWER))
#define DNS320L_VAL_LOW		(0)

/* high GPIO's */
#define DNS320L_OE_HIGH		(~(0))
#define DNS320L_VAL_HIGH	(0)

/* PHY related */
#define MV88E1318_PGADR_REG		22
#define MV88E1318_MAC_CTRL_PG	2
#define MV88E1318_MAC_CTRL_REG	21
#define MV88E1318_RGMII_TX_CTRL	(1 << 4)
#define MV88E1318_RGMII_RX_CTRL	(1 << 5)
#define MV88E1318_LED_PG		3
#define MV88E1318_LED_POL_REG	17
#define MV88E1318_LED2_4		(1 << 4)
#define MV88E1318_LED2_5		(1 << 5)

#endif /* __DNS320L_H */
