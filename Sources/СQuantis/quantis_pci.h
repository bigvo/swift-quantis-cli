/*
 * Quantis PCI driver
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
 * terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation.
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
 * For history of changes, ChangeLog.txt
 */

#ifndef QUANTIS_PCI_H
#define QUANTIS_PCI_H

#ifdef __cplusplus
extern "C"
{
#endif

/** Vendor IDs */
#define VENDOR_ID_HESSO 0x179A

/** Devices IDs */
#define DEVICE_ID_QUANTIS_PCI 0x0001

/** Driver information */
#define QUANTIS_PCI_DRIVER_NAME "Quantis PCI/PCIe RNG driver"
#define QUANTIS_PCI_DRIVER_SHORTNAME "quantis_pci"
#define QUANTIS_PCI_DRIVER_AUTHOR "ID Quantique SA"
#define QUANTIS_PCI_DRIVER_VERSION 202
#define QUANTIS_PCI_DRIVER_LICENSE "Dual BSD/GPL"

#define QUANTIS_PCI_MAX_CARDS 10
#define QUANTIS_PCI_MAX_MODULES 4

#define QUANTIS_PCI_DEVICE_NAME "qrandom"

    /******************************************************************************
 * Linux specific definitions
 ******************************************************************************/

#if defined(__linux__) || defined(__FreeBSD__)
#ifdef DEBUG
#define LOG_DEBUG0(str)
#define LOG_DEBUG1(str, arg1)
#define LOG_DEBUG2(str, arg1, arg2)
#define LOG_DEBUG3(str, arg1, arg2, arg3)
#define LOG_DEBUG4(str, arg1, arg2, arg3, arg4)
#define LOG_DEBUG5(str, arg1, arg2, arg3, arg4, arg5)
#else
#define LOG_DEBUG0(str)
#define LOG_DEBUG1(str, arg1)
#define LOG_DEBUG2(str, arg1, arg2)
#define LOG_DEBUG3(str, arg1, arg2, arg3)
#define LOG_DEBUG4(str, arg1, arg2, arg3, arg4)
#define LOG_DEBUG5(str, arg1, arg2, arg3, arg4, arg5)
#endif

/* Magic key to ensure IOCTL are OK */
#define QUANTIS_IOC_MAGIC 'q'

/* get driver version */
#define QUANTIS_IOCTL_GET_DRIVER_VERSION _IOR(QUANTIS_IOC_MAGIC, 0, unsigned int)

/* get number of detected cards */
#define QUANTIS_IOCTL_GET_CARD_COUNT _IOR(QUANTIS_IOC_MAGIC, 1, unsigned int)

/* get mask of detected modules */
#define QUANTIS_IOCTL_GET_MODULES_MASK _IOR(QUANTIS_IOC_MAGIC, 2, unsigned int)

/* get card serial number */
#define QUANTIS_IOCTL_GET_BOARD_VERSION _IOR(QUANTIS_IOC_MAGIC, 3, unsigned int)

/* reset one board */
#define QUANTIS_IOCTL_RESET_BOARD _IO(QUANTIS_IOC_MAGIC, 4)

/* enable mask module */
#define QUANTIS_IOCTL_ENABLE_MODULE _IOW(QUANTIS_IOC_MAGIC, 5, unsigned int)

/* disable mask modules */
#define QUANTIS_IOCTL_DISABLE_MODULE _IOW(QUANTIS_IOC_MAGIC, 6, unsigned int)

/* set debug level */
/*#define QUANTIS_IOCTL_SET_DEBUG_LEVEL     _IOW(QUANTIS_IOC_MAGIC, 7, unsigned int)*/

/* get status of modules */
#define QUANTIS_IOCTL_GET_MODULES_STATUS _IOR(QUANTIS_IOC_MAGIC, 8, unsigned int)

#define QUANTIS_IOCTL_GET_PCI_BUS_DEVICE_ID _IOR(QUANTIS_IOC_MAGIC, 9, unsigned int)

#define QUANTIS_IOCTL_GET_AIS31_STARTUP_TESTS_REQUEST_FLAG _IOR(QUANTIS_IOC_MAGIC, 10, unsigned int)

#define QUANTIS_IOCTL_CLEAR_AIS31_STARTUP_TESTS_REQUEST_FLAG _IOW(QUANTIS_IOC_MAGIC, 11, unsigned int)

#define QUANTIS_IOCTL_GET_SERIAL_MAX_LENGTH 256
#define QUANTIS_IOCTL_GET_SERIAL _IOR(QUANTIS_IOC_MAGIC, 12, char[QUANTIS_IOCTL_GET_SERIAL_MAX_LENGTH])

/* max number of IOCTL */
/* #define QUANTIS_IOCTL_MAXNR 8 */
#endif /* __linux__ || __FreeBSD__ */

/******************************************************************************
 * Solaris specific definitions
 ******************************************************************************/

/* __sun works with both GCC and Sun compilers when running on Solaris (x86 and sparc) */
#ifdef __sun

    /* Some specific include for some functions (memcpy for instance) used in the interface are needed
when compiling in kernel mode. */
    // #ifdef _KERNEL
    // #include <sys/systm.h>
    // #include <sys/cmn_err.h>
    // #include <sys/ddi.h>
    // #include <sys/sunddi.h>
    // #endif

#ifdef DEBUG
#define LOG_DEBUG0(str) \
    cmn_err(CE_NOTE, str)
#define LOG_DEBUG1(str, arg1) \
    cmn_err(CE_NOTE, str, arg1)
#define LOG_DEBUG2(str, arg1, arg2) \
    cmn_err(CE_NOTE, str, arg1, arg2)
#define LOG_DEBUG3(str, arg1, arg2, arg3) \
    cmn_err(CE_NOTE, str, arg1, arg2, arg3)
#define LOG_DEBUG4(str, arg1, arg2, arg3, arg4) \
    cmn_err(CE_NOTE, str, arg1, arg2, arg3, arg4)
#define LOG_DEBUG5(str, arg1, arg2, arg3, arg4, arg5) \
    cmn_err(CE_NOTE, str, arg1, arg2, arg3, arg4, arg5)
#else
#define LOG_DEBUG0(str)
#define LOG_DEBUG1(str, arg1)
#define LOG_DEBUG2(str, arg1, arg2)
#define LOG_DEBUG3(str, arg1, arg2, arg3)
#define LOG_DEBUG4(str, arg1, arg2, arg3, arg4)
#define LOG_DEBUG5(str, arg1, arg2, arg3, arg4, arg5)
#endif

#define QUANTIS_IOC_MAGIC 'q'
#define QUANTIS_IOC (QUANTIS_IOC_MAGIC << 8)

#define QUANTIS_IOCTL_GET_DRIVER_VERSION (QUANTIS_IOC | 0)
#define QUANTIS_IOCTL_GET_CARD_COUNT (QUANTIS_IOC | 1)
#define QUANTIS_IOCTL_GET_MODULES_MASK (QUANTIS_IOC | 2)
#define QUANTIS_IOCTL_GET_BOARD_VERSION (QUANTIS_IOC | 3)
#define QUANTIS_IOCTL_RESET_BOARD (QUANTIS_IOC | 4)
#define QUANTIS_IOCTL_ENABLE_MODULE (QUANTIS_IOC | 5)
#define QUANTIS_IOCTL_DISABLE_MODULE (QUANTIS_IOC | 6)
#define QUANTIS_IOCTL_SET_DEBUG_LEVEL (QUANTIS_IOC | 7)
#define QUANTIS_IOCTL_GET_MODULES_STATUS (QUANTIS_IOC | 8)
#define QUANTIS_IOCTL_GET_PCI_BUS_DEVICE_ID (QUANTIS_IOC | 9)
#define QUANTIS_IOCTL_GET_AIS31_STARTUP_TESTS_REQUEST_FLAG (QUANTIS_IOC | 10)
#define QUANTIS_IOCTL_CLEAR_AIS31_STARTUP_TESTS_REQUEST_FLAG (QUANTIS_IOC | 11)

#endif /* __sun */

    /******************************************************************************
 * Windows specific definitions
 ******************************************************************************/

    /* NOTE: CURRENTLY WINDOWS DEFINITIONS ARE COMMENTED SINCE CODE WINDOWS' DRIVERS CODE IS IN A SEPARATE FOLDER */
    /*#ifdef _WIN32
#ifdef DEBUG
#define LOG_DEBUG0(str)
#define LOG_DEBUG1(str, arg1)
#define LOG_DEBUG2(str, arg1, arg2)
#define LOG_DEBUG3(str, arg1, arg2, arg3)
#define LOG_DEBUG4(str, arg1, arg2, arg3, arg4)
#define LOG_DEBUG5(str, arg1, arg2, arg3, arg4, arg5)
#else
#define LOG_DEBUG0(str)
#define LOG_DEBUG1(str, arg1)
#define LOG_DEBUG2(str, arg1, arg2)
#define LOG_DEBUG3(str, arg1, arg2, arg3)
#define LOG_DEBUG4(str, arg1, arg2, arg3, arg4)
#define LOG_DEBUG5(str, arg1, arg2, arg3, arg4, arg5)
#endif*/

    /* get number of detected cards */
    /*#define QUANTIS_IOCTL_GET_CARD_COUNT      CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
*/
    /* get mask of detected modules */
    /*#define QUANTIS_IOCTL_GET_MODULES_MASK    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
*/
    /* get card serial number */
    /*#define QUANTIS_IOCTL_GET_BOARD_VERSION   CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
*/
    /* reset one board */
    /*#define QUANTIS_IOCTL_RESET_BOARD         CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)
*/
    /* enable mask module */
    /*#define QUANTIS_IOCTL_ENABLE_MODULE       CTL_CODE(FILE_DEVICE_UNKNOWN, 0x804, METHOD_BUFFERED, FILE_ANY_ACCESS)
*/
    /* disable mask modules */
    /*#define QUANTIS_IOCTL_DISABLE_MODULE      CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)
*/
    /* set debug level */
    /* No more used
#define QUANTIS_IOCTL_SET_DEBUG_LEVEL     CTL_CODE(FILE_DEVICE_UNKNOWN, 0x806, METHOD_BUFFERED, FILE_ANY_ACCESS)
*/
    /* get status of modules */
    /*#define QUANTIS_IOCTL_GET_MODULES_STATUS  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x807, METHOD_BUFFERED, FILE_ANY_ACCESS)
*/
    /* get driver version */
    /*#define QUANTIS_IOCTL_GET_DRIVER_VERSION  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x808, METHOD_BUFFERED, FILE_ANY_ACCESS)
*/

    /*#endif*/ /* _WIN32 */

#ifdef __cplusplus
}
#endif

#endif /* QUANTIS_PCI_H */
