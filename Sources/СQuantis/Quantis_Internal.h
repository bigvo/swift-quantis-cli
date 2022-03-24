/*
 * Quantis internal functions
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

#ifndef QUANTIS_INTERNAL_H
#define QUANTIS_INTERNAL_H


// #ifndef _WIN32
///* On Windows DISABLE_QUANTIS_JAVA is provided by the compiler */
//#include "QuantisLibConfig.h"
//#endif


#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#include "Quantis.h"

#ifdef __cplusplus
extern "C"
{
#endif

  /** Default message for not available string value */
#define QUANTIS_NOT_AVAILABLE "Not available"

  /** Default message for no serial number */
#define QUANTIS_NO_SERIAL "S/N not available"

  /**
   * Library version
   * @warning: Don't forget to update Quantis.rc, QuantisPackages.cmake and QuantisExtensions/QuantisExtractor.h too!
   */
#define QUANTIS_LIBRARY_VERSION 20.2f

  /**
   * Maximal number of Quantis devices allowed on the system. Note that a
   * maximal Quantis device limit may also be defined in the PCI driver itself!
   */
#define MAX_QUANTIS_DEVICE 127

  /** Data rate (in Bytes per second) of a single Quantis module */
#define QUANTIS_MODULE_DATA_RATE 500000

  /*************************** Internal functions ***************************
   *
   * NOTE: Definition of all internal function is in Quantis_C.c!
   *
   */

  /**
   * Open the Quantis device.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param deviceHandle a pointer to a pointer to a handle the device
   * @return The number of read bytes on success or a QUANTIS_ERROR code on failure.
   */
  int QuantisOpenInternal(QuantisDeviceType deviceType,
                          unsigned int deviceNumber,
                          QuantisDeviceHandle **deviceHandle);

  /**
   * Close the Quantis device.
   * This function close a previously opened device
   * @param deviceHandle a pointer to a handle the device
   */
  void QuantisCloseInternal(QuantisDeviceHandle *deviceHandle);

  /**
   * Count the number of bits in values that are set (that is they are 1)
   */
  int QuantisCountSetBits(int value);

  /******************** Quantis PCI functions declarations ********************
   *
   * Definition of Quantis PCI function is in QuantisPci_MyOs.c
   *
   */


  int CountFiles(char *Dir,char *Prefix);
  int CountPciDevs();
  

  
#ifndef DISABLE_QUANTIS_PCI

  int QuantisPciBoardReset(QuantisDeviceHandle *deviceHandle);

  void QuantisPciClose(QuantisDeviceHandle *deviceHandle);

  int QuantisPciCount();

  int QuantisPciGetBoardVersion(QuantisDeviceHandle *deviceHandle);

  float QuantisPciGetDriverVersion();

  char *QuantisPciGetManufacturer(QuantisDeviceHandle *deviceHandle);

  int QuantisPciGetModulesMask(QuantisDeviceHandle *deviceHandle);

  int QuantisPciGetModulesDataRate(QuantisDeviceHandle *deviceHandle);

  int QuantisPciGetModulesPower(QuantisDeviceHandle *deviceHandle);

  int QuantisPciGetModulesStatus(QuantisDeviceHandle *deviceHandle);

  char *QuantisPciGetSerialNumber(QuantisDeviceHandle *deviceHandle);

  int QuantisPciModulesDisable(QuantisDeviceHandle *deviceHandle,
                               int moduleMask);

  int QuantisPciModulesEnable(QuantisDeviceHandle *deviceHandle,
                              int moduleMask);

  int QuantisPciOpen(QuantisDeviceHandle *deviceHandle);

  int QuantisPciRead(QuantisDeviceHandle *deviceHandle,
                     void *buffer,
                     size_t size);

  int QuantisPciGetBusDeviceId(QuantisDeviceHandle *deviceHandle);

  char *QuantisPciTypeStrError(int errorNumber);

  int QuantisPciGetAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle);

  int QuantisPciClearAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle);

#endif /* DISABLE_QUANTIS_PCI */

  /******************** Quantis USB functions declarations ********************
   *
   * Definition of Quantis USB function is in QuantisUsb_MyOs.c
   *
   */

#ifndef DISABLE_QUANTIS_USB

  int QuantisUsbBoardReset(QuantisDeviceHandle *deviceHandle);

  void QuantisUsbClose(QuantisDeviceHandle *deviceHandle);

  int QuantisUsbCount();

  int QuantisUsbGetBoardVersion(QuantisDeviceHandle *deviceHandle);

  float QuantisUsbGetDriverVersion();

  char *QuantisUsbGetManufacturer(QuantisDeviceHandle *deviceHandle);

  int QuantisUsbGetModulesMask(QuantisDeviceHandle *deviceHandle);

  int QuantisUsbGetModulesDataRate(QuantisDeviceHandle *deviceHandle);

  int QuantisUsbGetModulesPower(QuantisDeviceHandle *deviceHandle);

  int QuantisUsbGetModulesStatus(QuantisDeviceHandle *deviceHandle);

  char *QuantisUsbGetSerialNumber(QuantisDeviceHandle *deviceHandle);

  int QuantisUsbModulesDisable(QuantisDeviceHandle *deviceHandle,
                               int moduleMask);

  int QuantisUsbModulesEnable(QuantisDeviceHandle *deviceHandle,
                              int moduleMask);

  int QuantisUsbOpen(QuantisDeviceHandle *deviceHandle);

  int QuantisUsbRead(QuantisDeviceHandle *deviceHandle,
                     void *buffer,
                     size_t size);

  int QuantisUsbGetBusDeviceId(QuantisDeviceHandle *deviceHandle);

  char *QuantisUsbTypeStrError(int errorNumber);

  int QuantisUsbGetAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle);

  int QuantisUsbClearAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle);

#endif /* DISABLE_QUANTIS_USB */

#ifdef __cplusplus
}
#endif

#endif // QUANTIS_INTERNAL_H
