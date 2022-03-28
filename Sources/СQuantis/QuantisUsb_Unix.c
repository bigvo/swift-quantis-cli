/*
 * Quantis USB Library for Unix systems
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
 * For history of changes, see ChangeLog.txt
 */

//#include "QuantisLibConfig.h"

#ifndef DISABLE_QUANTIS_USB

#if !(defined(unix) || defined(__unix) || defined(__unix__) || \
      defined(__APPLE__))
#error "This module is for Unix only!"
#endif

#ifdef __FreeBSD__
#include <libusb.h>
#else
#include <libusb.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// #include "GID.h"
#include "Quantis.h"
#include "Quantis_Internal.h"
#include "QuantisUsb_Commands.h"

/* Driver version == libusb version */
#define DRIVER_VERSION 1.0f

/* --------------------- Internal Methods & structures --------------------- */

/**
 * QuantisDeviceHandlePrivateData for Quantis USB on Unix
 */
typedef struct QuantisPrivateData
{
  libusb_device_handle *libusbDeviceHandle;
  libusb_context *libusbContext;
  char serialNumber[255];
  char manufacturer[255];
  unsigned int usbMaxPacketSize;
} QuantisPrivateData;

static int QuantisUsbGetIntValue(QuantisDeviceHandle *deviceHandle, char request)
{
  QuantisPrivateData *_privateData = (QuantisPrivateData *)deviceHandle->privateData;
  int result;
  uint8_t requestType;
  uint16_t wValue = 0;
  uint16_t wIndex = 0;
  unsigned char buffer[4];
  requestType = LIBUSB_REQUEST_TYPE_VENDOR |
                LIBUSB_RECIPIENT_INTERFACE |
                LIBUSB_ENDPOINT_IN;
  result = libusb_control_transfer(_privateData->libusbDeviceHandle,
                                   requestType,
                                   request,
                                   wValue,
                                   wIndex,
                                   (unsigned char *)buffer,
                                   sizeof(buffer),
                                   QUANTIS_USB_REQUEST_TIMEOUT);
  if (result < 0)
  {

    return QUANTIS_ERROR_IO;
  }

  result = buffer[0] |
           buffer[1] << 8 |
           buffer[2] << 16 |
           buffer[3] << 24;

  return result;
}

static int QuantisUsbGetUCHARValue(QuantisDeviceHandle *deviceHandle, char request)
{
  QuantisPrivateData *_privateData = (QuantisPrivateData *)deviceHandle->privateData;
  int result;
  uint8_t requestType;
  uint16_t wValue = 0;
  uint16_t wIndex = 0;
  unsigned char buffer[1];
  requestType = LIBUSB_REQUEST_TYPE_VENDOR |
                LIBUSB_RECIPIENT_INTERFACE |
                LIBUSB_ENDPOINT_IN;
  result = libusb_control_transfer(_privateData->libusbDeviceHandle,
                                   requestType,
                                   request,
                                   wValue,
                                   wIndex,
                                   buffer,
                                   sizeof(buffer),
                                   QUANTIS_USB_REQUEST_TIMEOUT);
  if (result < 0)
  {
    return QUANTIS_ERROR_IO;
  }

  return (int)buffer[0];
}

static int QuantisUsbSendRequest(QuantisDeviceHandle *deviceHandle, char request)
{
  QuantisPrivateData *_privateData = (QuantisPrivateData *)deviceHandle->privateData;
  int result;
  uint8_t requestType;
  uint16_t wValue = 0;
  uint16_t wIndex = 0;
  requestType = LIBUSB_REQUEST_TYPE_VENDOR |
                LIBUSB_RECIPIENT_INTERFACE |
                LIBUSB_ENDPOINT_OUT;
  result = libusb_control_transfer(_privateData->libusbDeviceHandle,
                                   requestType,
                                   request,
                                   wValue,
                                   wIndex,
                                   NULL,
                                   0,
                                   QUANTIS_USB_REQUEST_TIMEOUT);
  if (result < 0)
  {
    return QUANTIS_ERROR_IO;
  }

  return QUANTIS_SUCCESS;
}

/* --------------------------- QuantisUsb Methods --------------------------- */

/* Board reset */
int QuantisUsbBoardReset(QuantisDeviceHandle *deviceHandle)
{
  char buffer[4096];

  if ((QuantisUsbGetModulesStatus(deviceHandle) != 0x0001) ||
      (QuantisUsbGetModulesMask(deviceHandle) != 0x0000))
  {
    QuantisUsbModulesDisable(deviceHandle, 0xFFFFFFFF);
    QuantisUsbModulesEnable(deviceHandle, 0xFFFFFFFF);
    sleep(1);
  }

  return QuantisUsbRead(deviceHandle, buffer, 4096);
}

/* Close */
void QuantisUsbClose(QuantisDeviceHandle *deviceHandle)
{
  QuantisPrivateData *_privateData = (QuantisPrivateData *)deviceHandle->privateData;

  if (!_privateData)
  {
    return;
  }

  libusb_release_interface(_privateData->libusbDeviceHandle, 0);
  libusb_close(_privateData->libusbDeviceHandle);
  libusb_exit(_privateData->libusbContext);

  free(_privateData);
  _privateData = NULL;
}

/* Count */
int QuantisUsbCount()
{
  int result = 0;
  libusb_device *dev = NULL;
  libusb_device **usbDevices = NULL;
  libusb_context *libusbContext = NULL;
  int quantisUsbCount = 0;
  int i = 0;

  /* Initialize libusb */
  result = libusb_init(&libusbContext);
  if (result != LIBUSB_SUCCESS)
  {
    result = QUANTIS_ERROR_IO;
    goto cleanupContext;
  }

  /* Returns a list of USB devices currently attached to the system */
  if (libusb_get_device_list(libusbContext, &usbDevices) < 0)
  {
    result = QUANTIS_ERROR_IO;
    goto cleanup;
  }

  /* Search Quantis USB devices */
  while ((dev = usbDevices[i++]) != NULL)
  {
    struct libusb_device_descriptor desc;
    memset(&desc, 0, sizeof(desc));

    result = libusb_get_device_descriptor(dev, &desc);
    if (result < 0)
    {
      result = QUANTIS_ERROR_IO;
      goto cleanup;
    }

    if ((desc.idVendor == VENDOR_ID_ELLISYS) &&
        (desc.idProduct == DEVICE_ID_QUANTIS_USB))
    {
      quantisUsbCount++;
    }
  }

  result = quantisUsbCount;

cleanup:
  libusb_free_device_list(usbDevices, 1);

cleanupContext:
  libusb_exit(libusbContext);

  return result;
}

/* GetBoardVersion */
int QuantisUsbGetBoardVersion(QuantisDeviceHandle *deviceHandle)
{
  return QuantisUsbGetIntValue(deviceHandle, QUANTIS_USB_CMD_GET_BOARD_VERSION);
}

/* GetDriverVersion */
float QuantisUsbGetDriverVersion()
{
  return DRIVER_VERSION;
}

/* GetManufacturer */
char *QuantisUsbGetManufacturer(QuantisDeviceHandle *deviceHandle)
{
  QuantisPrivateData *_privateData = (QuantisPrivateData *)deviceHandle->privateData;
  return _privateData->manufacturer;
}

/* GetModulesMask */
int QuantisUsbGetModulesMask(QuantisDeviceHandle *deviceHandle)
{
  return QuantisUsbGetUCHARValue(deviceHandle, QUANTIS_USB_CMD_GET_MODULES_MASK);
}

/* GetSerialNumber */
char *QuantisUsbGetSerialNumber(QuantisDeviceHandle *deviceHandle)
{
  QuantisPrivateData *_privateData = (QuantisPrivateData *)deviceHandle->privateData;
  return _privateData->serialNumber;
}

/* GetModulesDataRate */
int QuantisUsbGetModulesDataRate(QuantisDeviceHandle *deviceHandle)
{
  int modulesRate = QuantisUsbGetIntValue(deviceHandle, QUANTIS_USB_CMD_GET_MODULES_RATE);

  if (modulesRate < 0)
  {
    return modulesRate;
  }
  /* loaded modules rate is in kbit/s. Converting in Bytes per second */
  modulesRate = modulesRate * 1000 / 8;

  int modulesMask = QuantisUsbGetModulesMask(deviceHandle);
  if (modulesMask < 0)
  {
    return modulesMask;
  }

  return modulesRate * QuantisCountSetBits(modulesMask);
}

/* GetModulesPower */
int QuantisUsbGetModulesPower(QuantisDeviceHandle *deviceHandle)
{
  return QuantisUsbGetUCHARValue(deviceHandle, QUANTIS_USB_CMD_GET_MODULES_POWER);
}

/* GetModulesStatus */
int QuantisUsbGetModulesStatus(QuantisDeviceHandle *deviceHandle)
{
  return QuantisUsbGetUCHARValue(deviceHandle, QUANTIS_USB_CMD_GET_MODULES_STATUS);
}

/* ModulesDisable */
int QuantisUsbModulesDisable(QuantisDeviceHandle *deviceHandle, int moduleMask)
{
  if ((moduleMask & 0x0001) != (0x0001))
  {
    /* Quantis USB only has one module... */
    return QUANTIS_ERROR_INVALID_PARAMETER;
  }

  return QuantisUsbSendRequest(deviceHandle, QUANTIS_USB_CMD_MODULE_DISABLE);
}

/* ModulesEnable */
int QuantisUsbModulesEnable(QuantisDeviceHandle *deviceHandle, int moduleMask)
{
  if ((moduleMask & 0x0001) != (0x0001))
  {
    /* Quantis USB only has one module... */
    return QUANTIS_ERROR_INVALID_PARAMETER;
  }

  return QuantisUsbSendRequest(deviceHandle, QUANTIS_USB_CMD_MODULE_ENABLE);
}

/* GetAis31StartupTestsRequestFlag */
int QuantisUsbGetAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle)
{
  return QuantisUsbGetUCHARValue(deviceHandle, QUANTIS_USB_CMD_GET_AIS31_STARTUP_TESTS_REQUEST_FLAG);
}

/* ClearAis31StartupTestsRequestFlag */
int QuantisUsbClearAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle)
{
  return QuantisUsbSendRequest(deviceHandle, QUANTIS_USB_CMD_CLEAR_AIS31_STARTUP_TESTS_REQUEST_FLAG);
}

/* Open */
int QuantisUsbOpen(QuantisDeviceHandle *deviceHandle)
{
  ssize_t usbDevicesCount = 0;
  int result = 0;
  libusb_device *dev = NULL;
  libusb_device **usbDevices = NULL;
  libusb_device **quantisUsbDevices = NULL;
  libusb_device_handle *libusbDeviceHandle = NULL;
  libusb_context *libusbContext = NULL;
  struct libusb_device_descriptor desc;
  struct libusb_config_descriptor *usbConfig = NULL;
  struct libusb_interface usbInterface;
  struct libusb_interface_descriptor usbInterfaceDescriptor;

  QuantisPrivateData *_privateData = NULL;
  int quantisUsbCount = 0;
  int i = 0;

  /* Initialize libusb */
  result = libusb_init(&libusbContext);
  if (result != LIBUSB_SUCCESS)
  {
    result = QUANTIS_ERROR_IO;
    goto cleanupContext;
  }

  /* Disable libusb messages */
  libusb_set_debug(libusbContext, 0);

  /* Allocate memory for Quantis USB devices */
  quantisUsbDevices = malloc(sizeof(void *) * (MAX_QUANTIS_DEVICE + 1));
  if (!quantisUsbDevices)
  {
    result = QUANTIS_ERROR_NO_MEMORY;
    goto cleanupContext;
  }
  quantisUsbDevices[MAX_QUANTIS_DEVICE] = NULL;

  /* Returns a list of USB devices currently attached to the system */
  usbDevicesCount = libusb_get_device_list(libusbContext, &usbDevices);
  if (usbDevicesCount < 0)
  {
    result = QUANTIS_ERROR_IO;
    goto cleanup;
  }

  /* Search Quantis USB devices */
  i = 0;
  while ((dev = usbDevices[i++]) != NULL)
  {
    result = libusb_get_device_descriptor(dev, &desc);
    if (result != LIBUSB_SUCCESS)
    {
      result = QUANTIS_ERROR_IO;
      goto cleanup;
    }

    if ((desc.idVendor == VENDOR_ID_ELLISYS) &&
        (desc.idProduct == DEVICE_ID_QUANTIS_USB))
    {
      quantisUsbDevices[quantisUsbCount] = dev;
      quantisUsbCount++;
    }
  }

  /* Select Quantis USB */
  if ((quantisUsbCount == 0) || (quantisUsbCount < deviceHandle->deviceNumber))
  {
    result = QUANTIS_ERROR_NO_DEVICE;
    goto cleanup;
  }

  dev = quantisUsbDevices[deviceHandle->deviceNumber];

  /* Load descriptor for selected device */
  result = libusb_get_device_descriptor(dev, &desc);
  if (result != LIBUSB_SUCCESS)
  {
    result = QUANTIS_ERROR_IO;
    goto cleanup;
  }

  /* Open device */
  result = libusb_open(dev, &libusbDeviceHandle);
  if (result != LIBUSB_SUCCESS)
  {
    result = QUANTIS_ERROR_IO;
    goto cleanup;
  }

  /* Set the active configuration for a device.*/
  result = libusb_set_configuration(libusbDeviceHandle, 1);
  if (result != LIBUSB_SUCCESS)
  {
    result = QUANTIS_ERROR_IO;
    goto cleanup;
  }

  /* Claim interface */
  result = libusb_claim_interface(libusbDeviceHandle, 0);
  if (result != LIBUSB_SUCCESS)
  {
    result = QUANTIS_ERROR_IO;
    goto cleanup;
  }

  /* Allocate memory for private data */
  _privateData = (QuantisPrivateData *)malloc(sizeof(QuantisPrivateData));
  if (!_privateData)
  {
    result = QUANTIS_ERROR_NO_MEMORY;
    goto cleanup;
  }

  /* Set private data */
  _privateData->libusbContext = libusbContext;
  _privateData->libusbDeviceHandle = libusbDeviceHandle;

  /* Determine maximum packet size */
  result = libusb_get_config_descriptor(dev, 0, &usbConfig);
  if (result != LIBUSB_SUCCESS)
  {
    result = QUANTIS_ERROR_IO;
    goto cleanup;
  }

  if ((desc.bNumConfigurations != 1) || (usbConfig->bNumInterfaces != 1))
  {
    result = QUANTIS_ERROR_IO;
    goto cleanup;
  }

  usbInterface = usbConfig->interface[0];
  if (usbInterface.num_altsetting <= 0)
  {
    result = QUANTIS_ERROR_IO;
    goto cleanup;
  }

  usbInterfaceDescriptor = usbInterface.altsetting[0];
  if (usbInterfaceDescriptor.bNumEndpoints <= 0)
  {
    result = QUANTIS_ERROR_IO;
    goto cleanup;
  }

  _privateData->usbMaxPacketSize = usbInterfaceDescriptor.endpoint[0].wMaxPacketSize;

  libusb_free_config_descriptor(usbConfig);

  /* Get serial number */
  result = libusb_get_string_descriptor_ascii(libusbDeviceHandle,
                                              desc.iSerialNumber,
                                              (unsigned char *)_privateData->serialNumber,
                                              sizeof(_privateData->serialNumber) - 1);
  if (result < 0)
  {
    /* Unable to get serial. Set to NO SERIAL NUMBER */
    unsigned char serialNumberLength = (unsigned char)strlen(QUANTIS_NO_SERIAL);
    memcpy(_privateData->serialNumber, QUANTIS_NO_SERIAL, serialNumberLength);
    _privateData->serialNumber[serialNumberLength] = 0;
  }

  /* Get manufacturer */
  result = libusb_get_string_descriptor_ascii(libusbDeviceHandle,
                                              desc.iManufacturer,
                                              (unsigned char *)_privateData->manufacturer,
                                              sizeof(_privateData->manufacturer) - 1);
  if (result < 0)
  {
    /* Unable to get value. Set to N/A */
    unsigned char manufacturerLength = (unsigned char)strlen(QUANTIS_NOT_AVAILABLE);
    memcpy(_privateData->manufacturer, QUANTIS_NOT_AVAILABLE, manufacturerLength);
    _privateData->manufacturer[manufacturerLength] = 0;
  }

  deviceHandle->privateData = _privateData;

  result = QUANTIS_SUCCESS;

  /* Cleanup */
cleanup:
  free(quantisUsbDevices);

cleanupContext:
  libusb_free_device_list(usbDevices, 1);

  return result;
}

/* Read */
int QuantisUsbRead(QuantisDeviceHandle *deviceHandle, void *buffer, size_t size)
{
  QuantisPrivateData *_privateData = (QuantisPrivateData *)deviceHandle->privateData;
  unsigned char tempBuffer[USB_MAX_BULK_PACKET_SIZE];
  int result = 0;
  int readBytes = 0;
  int transferred = 0;

  while (readBytes < (int)size)
  {
    size_t chunkSize = size - readBytes;
    if (chunkSize > _privateData->usbMaxPacketSize)
    {
      chunkSize = _privateData->usbMaxPacketSize;
    }

    /* Check if the status of the module is ok */
    if (QuantisUsbGetModulesStatus(deviceHandle) <= 0)
    {
      return QUANTIS_ERROR_INVALID_STATUS;
    }

    /*
     * Read data
     *
     * NOTE: we MUST request usbMaxPacketSize data, otherwise the request fails...
     */
    result = libusb_bulk_transfer(_privateData->libusbDeviceHandle,
                                  QUANTIS_USB_ENDPOINT_BULK_IN,
                                  tempBuffer,
                                  _privateData->usbMaxPacketSize,
                                  &transferred,
                                  QUANTIS_USB_REQUEST_TIMEOUT);
    if ((result < 0) || (transferred != (int)_privateData->usbMaxPacketSize))
    {
      return result;
    }

    /* Copy data to user's buffer */
    memcpy((char *)buffer + readBytes, (char *)tempBuffer, chunkSize);

    readBytes += chunkSize;
  }

  return readBytes;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"

/* GetDeviceId */
int QuantisUsbGetBusDeviceId(QuantisDeviceHandle *deviceHandle)
{
  //only implemented with Unix PCI
  return 0;
}
#pragma GCC diagnostic warning "-Wunused-parameter"

#else
int unused; /* Silence `ISO C forbids an empty translation unit' warning.  */
#endif /* DISABLE_QUANTIS_USB */

char *QuantisUsbTypeStrError(int errorNumber)
{
  char const *msg = NULL;

  //msg = libusb_strerror(errorNumber);
  msg = libusb_error_name(errorNumber);

  return (char *)msg;
}
