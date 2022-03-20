/*
 * Quantis USB commands
 *
 * Copyright (C) 2004-2020 ID Quantique SA, Carouge/Geneva, Switzerland
 * All rights reserved.
 *
 * ----------------------------------------------------------------------------
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modification.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY.
 *
 * ----------------------------------------------------------------------------
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License version 2 as published by the Free Software 
 * Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * ----------------------------------------------------------------------------
 *
 * For history of changes, see ChangeLog.txt
 */

#ifndef QUANTIS_USB_COMMANDS_H
#define QUANTIS_USB_COMMANDS_H

#ifndef DISABLE_QUANTIS_USB

/** Vendor IDs */
#define VENDOR_ID_ELLISYS 0x0ABA

/** Devices IDs */
#define DEVICE_ID_QUANTIS_USB 0x0102

/* Windows uses GUID to identify devices */
#ifdef _WIN32
#include <initguid.h>

/* {6476DB04-8D6C-49f5-BCF3-E2C1FC313A18} */
DEFINE_GUID(GUID_DEVINTERFACE_QUANTIS_USB,
            0x6476db04, 0x8d6c, 0x49f5, 0xbc, 0xf3, 0xe2, 0xc1, 0xfc, 0x31, 0x3a, 0x18);

#endif /* _WIN32 */

/* Timeout for request (in milliseconds */
#define QUANTIS_USB_REQUEST_TIMEOUT 1000

/* Defines QuantisUSB-specific commands */
#define QUANTIS_USB_CMD_GET_BOARD_VERSION 0x10
#define QUANTIS_USB_CMD_MODULE_DISABLE 0x11
#define QUANTIS_USB_CMD_MODULE_ENABLE 0x12
#define QUANTIS_USB_CMD_GET_MODULES_STATUS 0x13
#define QUANTIS_USB_CMD_GET_MODULES_POWER 0x14
#define QUANTIS_USB_CMD_GET_MODULES_MASK 0x15
#define QUANTIS_USB_CMD_GET_MODULES_RATE 0x16
#define QUANTIS_USB_CMD_GET_AIS31_STARTUP_TESTS_REQUEST_FLAG 0x17
#define QUANTIS_USB_CMD_CLEAR_AIS31_STARTUP_TESTS_REQUEST_FLAG 0x18

/**
   * Maximal size (in bytes) of an BULK packet.
   *
   * We have:
   *  - 64 bytes for USB 1
   *  - 512 bytes for USB 2
   */
#define USB_MAX_BULK_PACKET_SIZE 512

/**
   * Quantis USB Endpoint for bulk requests.
   * 
   * This can be seen in the device's descriptor, but since it do not change
   * we can define it here for faster execution.
   */
#define QUANTIS_USB_ENDPOINT_BULK_IN 0x86

#endif /* DISABLE_QUANTIS_USB */
#endif /* QUANTIS_USB_COMMANDS_H */
