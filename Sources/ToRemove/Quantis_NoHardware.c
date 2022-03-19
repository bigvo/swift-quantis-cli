/*
 * Hardware-less Quantis Library
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

#include <stddef.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Quantis.h"
#include "Quantis_Internal.h"

int modulesStatusPci = 15; /* 4 modules enabled */
int modulesStatusUsb = 1;  /* 1 module enabled */

int ais31StartupTestsRequestFlag = 1;

/**
 * A reentrant pseudo-random integer between 0 and 32767.
 * @param nextp returns the
 * @return a pseudo-random integer between 0 and 32767.
 */
int QuantisRandR(unsigned int *nextp)
{
  *nextp = *nextp * 1103515245 + 12345;
  return (unsigned int)(*nextp / 65536) % 32768;
}

/* Board reset */
int QuantisPciBoardReset(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */

  return QUANTIS_SUCCESS;
}

int QuantisUsbBoardReset(QuantisDeviceHandle *deviceHandle)
{
  return QuantisPciBoardReset(deviceHandle);
}

/* Close */
void QuantisPciClose(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
}

void QuantisUsbClose(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
}

/* Count */
int QuantisPciCount()
{
  /* One device detected */
  return 1;
}

int QuantisUsbCount()
{
  /* One device detected */
  return 1;
}

/* GetBoardVersion */
int QuantisPciGetBoardVersion(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  return 0;
}

int QuantisUsbGetBoardVersion(QuantisDeviceHandle *deviceHandle)
{
  return QuantisPciGetBoardVersion(deviceHandle);
}

/* GetDriverVersion */
float QuantisPciGetDriverVersion()
{
  return 0.1f; /* Version 0.1 */
}

float QuantisUsbGetDriverVersion()
{
  return QuantisPciGetDriverVersion();
}

/* GetManufacturer */
char *QuantisPciGetManufacturer(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  return (char *)QUANTIS_NOT_AVAILABLE;
}

char *QuantisUsbGetManufacturer(QuantisDeviceHandle *deviceHandle)
{
  return QuantisPciGetManufacturer(deviceHandle);
}

/* GetModulesMask */
int QuantisPciGetModulesMask(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  return 15;                   /* 4 modules */
}

int QuantisUsbGetModulesMask(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  return 1;                    /* 1 module */
}

/* GetModulesDataRate */
int QuantisPciGetModulesDataRate(QuantisDeviceHandle *deviceHandle)
{
  return QUANTIS_MODULE_DATA_RATE *
         QuantisCountSetBits(QuantisPciGetModulesMask(deviceHandle));
}

int QuantisUsbGetModulesDataRate(QuantisDeviceHandle *deviceHandle)
{
  return QuantisPciGetModulesDataRate(deviceHandle);
}

/* GetModulesStatus */
int QuantisPciGetModulesStatus(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  return modulesStatusPci;
}

int QuantisUsbGetModulesStatus(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  return modulesStatusUsb;
}

/* GetModulesPower */
int QuantisPciGetModulesPower(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  return 1;
}

int QuantisUsbGetModulesPower(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  return 1;
}

/* GetSerialNumber */
char *QuantisPciGetSerialNumber(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  return (char *)QUANTIS_NO_SERIAL;
}

char *QuantisUsbGetSerialNumber(QuantisDeviceHandle *deviceHandle)
{
  return QuantisPciGetSerialNumber(deviceHandle);
}

/* ModulesDisable */
int QuantisPciModulesDisable(QuantisDeviceHandle *deviceHandle, int moduleMask)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  modulesStatusPci = moduleMask;
  return QUANTIS_SUCCESS;
}

int QuantisUsbModulesDisable(QuantisDeviceHandle *deviceHandle, int moduleMask)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  modulesStatusUsb = moduleMask;
  return QUANTIS_SUCCESS;
}

/* ModulesEnable */
int QuantisPciModulesEnable(QuantisDeviceHandle *deviceHandle, int moduleMask)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  modulesStatusPci = moduleMask;
  return QUANTIS_SUCCESS;
}

int QuantisUsbModulesEnable(QuantisDeviceHandle *deviceHandle, int moduleMask)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  modulesStatusUsb = moduleMask;
  return QUANTIS_SUCCESS;
}

int QuantisPciGetBusDeviceId(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  return QUANTIS_SUCCESS;
}

int QuantisUsbGetBusDeviceId(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  return QUANTIS_SUCCESS;
}

/* ModulesReset */
int QuantisPciModulesReset(QuantisDeviceHandle *deviceHandle, int moduleMask)
{
  int result = QuantisPciModulesDisable(deviceHandle, moduleMask);
  if (result != QUANTIS_SUCCESS)
  {
    return result;
  }

  return QuantisPciModulesEnable(deviceHandle, moduleMask);
}

int QuantisUsbModulesReset(QuantisDeviceHandle *deviceHandle, int moduleMask)
{
  int result = QuantisUsbModulesDisable(deviceHandle, moduleMask);
  if (result != QUANTIS_SUCCESS)
  {
    return result;
  }

  return QuantisUsbModulesEnable(deviceHandle, moduleMask);
}

int QuantisPciGetAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  return ais31StartupTestsRequestFlag;
}

int QuantisUsbGetAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  return ais31StartupTestsRequestFlag;
}

int QuantisPciClearAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  ais31StartupTestsRequestFlag = 0;

  return QUANTIS_SUCCESS;
}

int QuantisUsbClearAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */
  ais31StartupTestsRequestFlag = 0;

  return QUANTIS_SUCCESS;
}

/* Open */
int QuantisPciOpen(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */

  return QUANTIS_SUCCESS;
}

int QuantisUsbOpen(QuantisDeviceHandle *deviceHandle)
{
  deviceHandle = deviceHandle; /* Avoids unused parameter warning */

  return QUANTIS_SUCCESS;
}

/* Read */
int QuantisPciRead(QuantisDeviceHandle *deviceHandle, void *buffer, size_t size)
{
  size_t readBytes = 0u;
  static unsigned int seed = 0u;
  unsigned char *charBuffer = (unsigned char *)buffer;

  /* Consistency check */
  if (size == 0)
  {
    /* Nothing to read */
    return 0;
  }

  /*
   * Use ops instead of directly calling QuantisPciGetModulesStatus
   * since QuantisUsbread also uses this function...
   */
  if (deviceHandle->ops->GetModulesStatus(deviceHandle) <= 0)
  {
    return QUANTIS_ERROR_NO_MODULE;
  }

  /* Using internal PRNG */
  while (readBytes < size)
  {
    *charBuffer++ = (unsigned char)QuantisRandR(&seed);
    readBytes++;
  }
  return (int)readBytes;
}

int QuantisUsbRead(QuantisDeviceHandle *deviceHandle, void *buffer, size_t size)
{
  return QuantisPciRead(deviceHandle, buffer, size);
}

char *QuantisPciTypeStrError(int errorNumber)
{
  return (char *)NULL;
}

char *QuantisUsbTypeStrError(int errorNumber)
{
  return (char *)NULL;
}
