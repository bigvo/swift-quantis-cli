/*
 * Quantis C library
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Conversion.h"
#include "Quantis.h"
#include "Quantis_Internal.h"

/* Internal variable to store serial number */
char serialNumber[256];

/* Internal variable to store manufactuer's name */
char manufactuer[256];

/* Size of the buffer used for QuantisReadXXX methods */
#define QUANTIS_READ_XXX_BUFFER_SIZE 8

#ifndef DISABLE_QUANTIS_PCI
QuantisOperations QuantisOperationsPci =
    {
        /*.BoardReset = */ QuantisPciBoardReset,
        /*.Close = */ QuantisPciClose,
        /*.Count = */ QuantisPciCount,
        /*.GetBoardVersion = */ QuantisPciGetBoardVersion,
        /*.GetDriverVersion = */ QuantisPciGetDriverVersion,
        /*.GetManufacturer = */ QuantisPciGetManufacturer,
        /*.GetModulesMask = */ QuantisPciGetModulesMask,
        /*.GetModulesDataRate = */ QuantisPciGetModulesDataRate,
        /*.GetModulesPower = */ QuantisPciGetModulesPower,
        /*.GetModulesStatus = */ QuantisPciGetModulesStatus,
        /*.GetSerialNumber = */ QuantisPciGetSerialNumber,
        /*.ModulesDisable = */ QuantisPciModulesDisable,
        /*.ModulesEnable = */ QuantisPciModulesEnable,
        /*.Open = */ QuantisPciOpen,
        /*.Read = */ QuantisPciRead,
        /*.GetBusDeviceId = */ QuantisPciGetBusDeviceId,
        /*.QuantisTypeStrError = */ QuantisPciTypeStrError,
        /*.GetAis31StartupTestsRequestFlag*/ QuantisPciGetAis31StartupTestsRequestFlag,
        /*.ClearAis31StartupTestsRequestFlag*/ QuantisPciClearAis31StartupTestsRequestFlag};
#endif /* DISABLE_QUANTIS_PCI */

#ifndef DISABLE_QUANTIS_USB
QuantisOperations QuantisOperationsUsb =
    {
        /*.BoardReset = */ QuantisUsbBoardReset,
        /*.Close = */ QuantisUsbClose,
        /*.Count = */ QuantisUsbCount,
        /*.GetBoardVersion = */ QuantisUsbGetBoardVersion,
        /*.GetDriverVersion = */ QuantisUsbGetDriverVersion,
        /*.GetManufacturer = */ QuantisUsbGetManufacturer,
        /*.GetModulesMask = */ QuantisUsbGetModulesMask,
        /*.GetModulesDataRate = */ QuantisUsbGetModulesDataRate,
        /*.GetModulesPower = */ QuantisUsbGetModulesPower,
        /*.GetModulesStatus = */ QuantisUsbGetModulesStatus,
        /*.GetSerialNumber = */ QuantisUsbGetSerialNumber,
        /*.ModulesDisable = */ QuantisUsbModulesDisable,
        /*.ModulesEnable = */ QuantisUsbModulesEnable,
        /*.Open = */ QuantisUsbOpen,
        /*.Read = */ QuantisUsbRead,
        /*.GetBusDeviceId = */ QuantisUsbGetBusDeviceId,
        /*.QuantisTypeStrError = */ QuantisUsbTypeStrError,
        /*.GetAis31StartupTestsRequestFlag*/ QuantisUsbGetAis31StartupTestsRequestFlag,
        /*.ClearAis31StartupTestsRequestFlag*/ QuantisUsbClearAis31StartupTestsRequestFlag

};
#endif /* DISABLE_QUANTIS_USB */

int QuantisBoardReset(QuantisDeviceType deviceType,
                      unsigned int deviceNumber)
{
  int result;
  QuantisDeviceHandle *deviceHandle = NULL;

  /* Open device */
  result = QuantisOpenInternal(deviceType, deviceNumber, &deviceHandle);
  if (result < 0)
  {
    return result;
  }

  /* Perform request */
  result = deviceHandle->ops->BoardReset(deviceHandle);

  /* Close device */
  QuantisCloseInternal(deviceHandle);

  return result;
}

void QuantisCloseInternal(QuantisDeviceHandle *deviceHandle)
{
  if (!deviceHandle)
  {
    return;
  }

  /* Frees privateData */
  if (deviceHandle->ops)
  {
    deviceHandle->ops->Close(deviceHandle);
  }
  deviceHandle->ops = NULL;
  deviceHandle->privateData = NULL;

  free(deviceHandle);
  deviceHandle = NULL;
}

int QuantisGetBoardVersion(QuantisDeviceType deviceType,
                           unsigned int deviceNumber)
{
  int result;
  QuantisDeviceHandle *deviceHandle = NULL;

  /* Open device */
  result = QuantisOpenInternal(deviceType, deviceNumber, &deviceHandle);
  if (result < 0)
  {
    return result;
  }

  /* Perform request */
  result = deviceHandle->ops->GetBoardVersion(deviceHandle);

  /* Close device */
  QuantisCloseInternal(deviceHandle);

  return result;
}

int QuantisCount(QuantisDeviceType deviceType)
{
  int result = QUANTIS_ERROR_OTHER;
  switch (deviceType)
  {
#ifndef DISABLE_QUANTIS_PCI
  case QUANTIS_DEVICE_PCI:
    result = QuantisOperationsPci.Count();
    break;
#endif /* DISABLE_QUANTIS_PCI */

#ifndef DISABLE_QUANTIS_USB
  case QUANTIS_DEVICE_USB:
    result = QuantisOperationsUsb.Count();
    break;
#endif /* DISABLE_QUANTIS_USB */

  default:
    result = 0;
    break;
  }

  return result;
}

int QuantisCountSetBits(int value)
{
  size_t i;
  int count = 0;
  for (i = 0; i < (sizeof(value) * 8); i++)
  {
    if (value & (1 << i))
    {
      count++;
    }
  }
  return count;
}

float QuantisGetDriverVersion(QuantisDeviceType deviceType)
{
  float result = (float)QUANTIS_ERROR_OTHER;
  switch (deviceType)
  {
#ifndef DISABLE_QUANTIS_PCI
  case QUANTIS_DEVICE_PCI:
    result = QuantisOperationsPci.GetDriverVersion();
    break;
#endif /* DISABLE_QUANTIS_PCI */

#ifndef DISABLE_QUANTIS_USB
  case QUANTIS_DEVICE_USB:
    result = QuantisOperationsUsb.GetDriverVersion();
    break;
#endif /* DISABLE_QUANTIS_USB */

  default:
    result = (float)QUANTIS_ERROR_NO_DRIVER;
    break;
  }

  return result;
}

char *QuantisGetManufacturer(QuantisDeviceType deviceType,
                             unsigned int deviceNumber)
{
  int result = 0;
  char *sn = NULL;
  QuantisDeviceHandle *deviceHandle = NULL;

  /* Open device */
  result = QuantisOpenInternal(deviceType, deviceNumber, &deviceHandle);
  if (result < 0)
  {
    return (char *)QUANTIS_NOT_AVAILABLE;
  }

  /* Perform request and copy string locally */
  sn = deviceHandle->ops->GetManufacturer(deviceHandle);
  memcpy(manufactuer, sn, strlen(sn));
  manufactuer[strlen(sn)] = 0;

  QuantisCloseInternal(deviceHandle);

  return manufactuer;
}

int QuantisGetModulesCount(QuantisDeviceType deviceType,
                           unsigned int deviceNumber)
{
  int result = QuantisGetModulesMask(deviceType, deviceNumber);
  if (result < 0)
  {
    return result;
  }

  return QuantisCountSetBits(result);
}

int QuantisGetModulesMask(QuantisDeviceType deviceType,
                          unsigned int deviceNumber)
{
  int result;
  QuantisDeviceHandle *deviceHandle = NULL;

  /* Open device */
  result = QuantisOpenInternal(deviceType, deviceNumber, &deviceHandle);
  if (result < 0)
  {
    return result;
  }

  /* Perform request */
  result = deviceHandle->ops->GetModulesMask(deviceHandle);

  /* Close device */
  QuantisCloseInternal(deviceHandle);

  return result;
}

float QuantisGetLibVersion()
{
  return QUANTIS_LIBRARY_VERSION;
}

int QuantisGetModulesDataRate(QuantisDeviceType deviceType,
                              unsigned int deviceNumber)
{
  int result;
  QuantisDeviceHandle *deviceHandle = NULL;

  /* Open device */
  result = QuantisOpenInternal(deviceType, deviceNumber, &deviceHandle);
  if (result < 0)
  {
    return result;
  }

  /* Perform request */
  result = deviceHandle->ops->GetModulesDataRate(deviceHandle);

  /* Close device */
  QuantisCloseInternal(deviceHandle);

  return result;
}

int QuantisGetModulesPower(QuantisDeviceType deviceType,
                           unsigned int deviceNumber)
{
  int result;
  QuantisDeviceHandle *deviceHandle = NULL;

  /* Open device */
  result = QuantisOpenInternal(deviceType, deviceNumber, &deviceHandle);
  if (result < 0)
  {
    return result;
  }

  /* Perform request */
  result = deviceHandle->ops->GetModulesPower(deviceHandle);

  /* Close device */
  QuantisCloseInternal(deviceHandle);

  return result;
}

int QuantisGetModulesStatus(QuantisDeviceType deviceType,
                            unsigned int deviceNumber)
{
  int result;
  QuantisDeviceHandle *deviceHandle = NULL;

  /* Open device */
  result = QuantisOpenInternal(deviceType, deviceNumber, &deviceHandle);
  if (result < 0)
  {
    return result;
  }

  /* Perform request */
  result = deviceHandle->ops->GetModulesStatus(deviceHandle);

  /* Close device */
  QuantisCloseInternal(deviceHandle);

  return result;
}

char *QuantisGetSerialNumber(QuantisDeviceType deviceType,
                             unsigned int deviceNumber)
{
  int result = 0;
  char *sn = NULL;
  QuantisDeviceHandle *deviceHandle = NULL;

  /* Open device */
  result = QuantisOpenInternal(deviceType, deviceNumber, &deviceHandle);
  if (result < 0)
  {
    return (char *)QUANTIS_NO_SERIAL;
  }

  /* Perform request and copy serial number locally */
  sn = deviceHandle->ops->GetSerialNumber(deviceHandle);
  memcpy(serialNumber, sn, strlen(sn));
  serialNumber[strlen(sn)] = 0;

  QuantisCloseInternal(deviceHandle);

  return serialNumber;
}

int QuantisModulesDisable(QuantisDeviceType deviceType,
                          unsigned int deviceNumber,
                          int modulesMask)
{
  int result;
  QuantisDeviceHandle *deviceHandle = NULL;

  /* Open device */
  result = QuantisOpenInternal(deviceType, deviceNumber, &deviceHandle);
  if (result < 0)
  {
    return result;
  }

  /* Perform request */
  result = deviceHandle->ops->ModulesDisable(deviceHandle, modulesMask);

  /* Close device */
  QuantisCloseInternal(deviceHandle);

  return result;
}

int QuantisModulesEnable(QuantisDeviceType deviceType,
                         unsigned int deviceNumber,
                         int modulesMask)
{
  int result;
  QuantisDeviceHandle *deviceHandle = NULL;

  /* Open device */
  result = QuantisOpenInternal(deviceType, deviceNumber, &deviceHandle);
  if (result < 0)
  {
    return result;
  }

  /* Perform request */
  result = deviceHandle->ops->ModulesEnable(deviceHandle, modulesMask);

  /* Close device */
  QuantisCloseInternal(deviceHandle);

  return result;
}

int QuantisModulesReset(QuantisDeviceType deviceType,
                        unsigned int deviceNumber,
                        int modulesMask)
{
  int result;
  QuantisDeviceHandle *deviceHandle = NULL;

  /* Open device */
  result = QuantisOpenInternal(deviceType, deviceNumber, &deviceHandle);
  if (result < 0)
  {
    return result;
  }

  /* Perform request */
  result = deviceHandle->ops->ModulesDisable(deviceHandle, modulesMask);
  if (result == QUANTIS_SUCCESS)
  {
    result = deviceHandle->ops->ModulesEnable(deviceHandle, modulesMask);
  }

  /* Close device */
  QuantisCloseInternal(deviceHandle);

  return result;
}

int QuantisGetAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle)
{
  int result;

  if (deviceHandle == NULL)
  {
    return QUANTIS_ERROR_IO;
  }

  /* Perform request */
  result = deviceHandle->ops->GetAis31StartupTestsRequestFlag(deviceHandle);

  return result;
}

int QuantisClearAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle)
{
  int result;

  if (deviceHandle == NULL)
  {
    return QUANTIS_ERROR_IO;
  }

  /* Perform request */
  result = deviceHandle->ops->ClearAis31StartupTestsRequestFlag(deviceHandle);

  return result;
}

int QuantisOpenInternal(QuantisDeviceType deviceType,
                        unsigned int deviceNumber,
                        QuantisDeviceHandle **deviceHandle)
{
  QuantisDeviceHandle *_deviceHandle = NULL;
  QuantisOperations *quantisOperations = NULL;
  int result = 0;

  /* Consistency checks */
  if (deviceNumber >= MAX_QUANTIS_DEVICE)
  {
    return QUANTIS_ERROR_INVALID_DEVICE_NUMBER;
  }

  switch (deviceType)
  {
#ifndef DISABLE_QUANTIS_PCI
  case QUANTIS_DEVICE_PCI:
    quantisOperations = &QuantisOperationsPci;
    break;
#endif /* DISABLE_QUANTIS_PCI */

#ifndef DISABLE_QUANTIS_USB
  case QUANTIS_DEVICE_USB:
    quantisOperations = &QuantisOperationsUsb;
    break;
#endif /* DISABLE_QUANTIS_USB */

  default:
    return QUANTIS_ERROR_NO_DEVICE;
    break;
  }

  /* Allocate memory */
  _deviceHandle = malloc(sizeof(QuantisDeviceHandle));
  if (!_deviceHandle)
  {
    return QUANTIS_ERROR_NO_MEMORY;
  }

  /* Set device info */
  _deviceHandle->deviceNumber = deviceNumber;
  _deviceHandle->deviceType = deviceType;
  _deviceHandle->ops = quantisOperations;
  _deviceHandle->privateData = NULL;

  /* Open device */
  result = _deviceHandle->ops->Open(_deviceHandle);
  if (result < 0)
  {
    /* Error while opening device */
    QuantisCloseInternal(_deviceHandle);
    _deviceHandle = NULL;
  }

  *deviceHandle = _deviceHandle;

  return result;
}

int QuantisRead(QuantisDeviceType deviceType,
                unsigned int deviceNumber,
                void *buffer,
                size_t size)
{
  int result;
  QuantisDeviceHandle *deviceHandle = NULL;

  if (size == 0u)
  {
    return 0;
  }
  else if (size > QUANTIS_MAX_READ_SIZE)
  {
    return QUANTIS_ERROR_INVALID_READ_SIZE;
  }

  /* Open device */
  result = QuantisOpenInternal(deviceType, deviceNumber, &deviceHandle);
  if (result < 0)
  {
    return result;
  }

  /* Read data */
  result = deviceHandle->ops->Read(deviceHandle, buffer, size);

  /* Close device */
  QuantisCloseInternal(deviceHandle);
  deviceHandle = NULL;

  return result;
}

int QuantisOpen(QuantisDeviceType deviceType,
                unsigned int deviceNumber,
                QuantisDeviceHandle **deviceHandle)
{
  return QuantisOpenInternal(deviceType,
                             deviceNumber,
                             deviceHandle);
}

void QuantisClose(QuantisDeviceHandle *deviceHandle)
{
  QuantisCloseInternal(deviceHandle);
}

int QuantisReadHandled(QuantisDeviceHandle *deviceHandle,
                       void *buffer,
                       size_t size)
{
  int result;

  if (deviceHandle == NULL)
  {
    return QUANTIS_ERROR_IO;
  }

  if (size == 0u)
  {
    return 0;
  }
  else if (size > QUANTIS_MAX_READ_SIZE)
  {
    return QUANTIS_ERROR_INVALID_READ_SIZE;
  }

  // Read data
  result = deviceHandle->ops->Read(deviceHandle, buffer, size);

  return result;
}

int QuantisReadDouble_01(QuantisDeviceType deviceType,
                         unsigned int deviceNumber,
                         double *value)
{
  int size = sizeof(*value);
  char buffer[QUANTIS_READ_XXX_BUFFER_SIZE];

  int result = QuantisRead(deviceType, deviceNumber, buffer, size);
  if (result < 0)
  {
    return result;
  }
  else if (result != size)
  {
    return QUANTIS_ERROR_IO;
  }

  *value = ConvertToDouble_01(buffer);

  return QUANTIS_SUCCESS;
}

int QuantisReadFloat_01(QuantisDeviceType deviceType,
                        unsigned int deviceNumber,
                        float *value)
{
  int size = sizeof(*value);
  char buffer[QUANTIS_READ_XXX_BUFFER_SIZE];

  int result = QuantisRead(deviceType, deviceNumber, buffer, size);
  if (result < 0)
  {
    return result;
  }
  else if (result != size)
  {
    return QUANTIS_ERROR_IO;
  }

  *value = ConvertToFloat_01(buffer);

  return QUANTIS_SUCCESS;
}

int QuantisReadInt(QuantisDeviceType deviceType,
                   unsigned int deviceNumber,
                   int *value)
{
  int size = sizeof(*value);
  char buffer[QUANTIS_READ_XXX_BUFFER_SIZE];

  int result = QuantisRead(deviceType, deviceNumber, buffer, size);
  if (result < 0)
  {
    return result;
  }
  else if (result != size)
  {
    return QUANTIS_ERROR_IO;
  }

  *value = ConvertToInt(buffer);

  return QUANTIS_SUCCESS;
}

int QuantisReadShort(QuantisDeviceType deviceType,
                     unsigned int deviceNumber,
                     short *value)
{
  int size = sizeof(*value);
  char buffer[QUANTIS_READ_XXX_BUFFER_SIZE];

  int result = QuantisRead(deviceType, deviceNumber, buffer, size);
  if (result < 0)
  {
    return result;
  }
  else if (result != size)
  {
    return QUANTIS_ERROR_IO;
  }

  *value = ConvertToShort(buffer);

  return QUANTIS_SUCCESS;
}

int QuantisReadScaledDouble(QuantisDeviceType deviceType,
                            unsigned int deviceNumber,
                            double *value,
                            double min,
                            double max)
{
  double tmp;
  int result;

  if (min > max)
  {
    return QUANTIS_ERROR_INVALID_PARAMETER;
  }

  result = QuantisReadDouble_01(deviceType, deviceNumber, &tmp);
  if (result != QUANTIS_SUCCESS)
  {
    return result;
  }

  *value = tmp * (max - min) + min;

  return QUANTIS_SUCCESS;
}

int QuantisReadScaledFloat(QuantisDeviceType deviceType,
                           unsigned int deviceNumber,
                           float *value,
                           float min,
                           float max)
{
  float tmp;
  int result;

  if (min > max)
  {
    return QUANTIS_ERROR_INVALID_PARAMETER;
  }

  result = QuantisReadFloat_01(deviceType, deviceNumber, &tmp);
  if (result != QUANTIS_SUCCESS)
  {
    return result;
  }

  *value = tmp * (max - min) + min;

  return QUANTIS_SUCCESS;
}

int QuantisReadScaledInt(QuantisDeviceType deviceType,
                         unsigned int deviceNumber,
                         int *value,
                         int min,
                         int max)
{
  int tmp;
  int result;

  const int BITS = sizeof(tmp) * 8;
  const unsigned long long RANGE = max - min + 1;
  const unsigned long long MAX_RANGE = 1ull << BITS;
  const unsigned long long LIMIT = MAX_RANGE - (MAX_RANGE % RANGE);

  if (min > max)
  {
    return QUANTIS_ERROR_INVALID_PARAMETER;
  }

  // Chooses the highest number that is the largest multiple of the output range
  // (discard values higher the output range)
  do
  {
    result = QuantisReadInt(deviceType, deviceNumber, &tmp);
    if (result != QUANTIS_SUCCESS)
    {
      return result;
    }
  } while ((tmp > 0) && ((unsigned long long)tmp >= LIMIT));

  *value = (tmp % RANGE) + min;

  return QUANTIS_SUCCESS;
}

int QuantisReadScaledShort(QuantisDeviceType deviceType,
                           unsigned int deviceNumber,
                           short *value,
                           short min,
                           short max)
{
  short tmp;
  int result;
  const int BITS = sizeof(tmp) * 8;
  const unsigned int RANGE = max - min + 1;
  const unsigned int MAX_RANGE = 1u << BITS;
  const unsigned int LIMIT = MAX_RANGE - (MAX_RANGE % RANGE);

  if (min > max)
  {
    return QUANTIS_ERROR_INVALID_PARAMETER;
  }

  // Chooses the highest number that is the largest multiple of the output range
  // (discard values higher the output range)
  do
  {
    result = QuantisReadShort(deviceType, deviceNumber, &tmp);
    if (result != QUANTIS_SUCCESS)
    {
      return result;
    }
  } while ((tmp > 0) && ((unsigned int)tmp >= LIMIT));

  *value = (tmp % RANGE) + min;

  return QUANTIS_SUCCESS;
}

char *QuantisStrError(QuantisError errorNumber)
{
  char const *msg = NULL;

  // Errors are listed alphabetically
  switch (errorNumber)
  {

  case QUANTIS_ERROR_INVALID_DEVICE_NUMBER:
    msg = "Invalid device number (out of bounds)";
    break;

  case QUANTIS_ERROR_NO_DRIVER:
    msg = "Invalid driver type";
    break;

  case QUANTIS_ERROR_INVALID_PARAMETER:
    msg = "Invalid parameter";
    break;

  case QUANTIS_ERROR_INVALID_READ_SIZE:
    msg = "Invalid size (size is negative or too large)";
    break;

  case QUANTIS_ERROR_IO:
    msg = "Input/output error";
    break;

  case QUANTIS_ERROR_NO_DEVICE:
    msg = "No such device (it may have been disconnected)";
    break;

  case QUANTIS_ERROR_NO_MEMORY:
    msg = "Memory allocation failure (insufficient memory?)";
    break;

  case QUANTIS_ERROR_NO_MODULE:
    msg = "No module found or no module enabled";
    break;

  case QUANTIS_ERROR_OPERATION_NOT_SUPPORTED:
    msg = "Operation is not supported or unimplemented";
    break;

  case QUANTIS_ERROR_INVALID_STATUS:
    msg = "the module returns an invalid status";
    break;

  case QUANTIS_SUCCESS:
    msg = "Success";
    break;

  case QUANTIS_ERROR_OTHER:
  default:
    break;
  }

  return (char *)msg;
}

char *QuantisFullStrError(QuantisDeviceType deviceType, QuantisError errorNumber)
{
  char const *msg = NULL;

  msg = QuantisStrError(errorNumber);

  if (msg == NULL)
  {
    switch (deviceType)
    {
#ifndef DISABLE_QUANTIS_PCI
    case QUANTIS_DEVICE_PCI:
      msg = QuantisOperationsPci.QuantisTypeStrError(errorNumber);
      break;
#endif /* DISABLE_QUANTIS_PCI */

#ifndef DISABLE_QUANTIS_USB
    case QUANTIS_DEVICE_USB:
      msg = QuantisOperationsUsb.QuantisTypeStrError(errorNumber);
      break;
#endif /* DISABLE_QUANTIS_USB */

    default:
      break;
    }
  }

  return (char *)msg;
}
