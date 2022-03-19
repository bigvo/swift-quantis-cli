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

#ifndef QUANTIS_H
#define QUANTIS_H

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#include "DllMain.h"

#ifdef __cplusplus
extern "C"
{
#endif

  /**
   * Type of Quantis device
   */
  DLL_EXPORT typedef enum {
    /** Quantis PCI or PCI-Express */
    QUANTIS_DEVICE_PCI = 1,

    /** Quantis USB */
    QUANTIS_DEVICE_USB = 2

    /* Next Quantis device type
    QUANTIS_DEVICE_XXX = 4 */
  } QuantisDeviceType;

  /**
   * List of errors for the Quantis.
   */
  DLL_EXPORT typedef enum {
    /** Success (no error) */
    QUANTIS_SUCCESS = 0,

    /** Invalid driver */
    QUANTIS_ERROR_NO_DRIVER = -101,

    /** Invalid device number (out of bounds) */
    QUANTIS_ERROR_INVALID_DEVICE_NUMBER = -102,

    /** Invalid size to read (too high) */
    QUANTIS_ERROR_INVALID_READ_SIZE = -103,

    /** Invalid parameter */
    QUANTIS_ERROR_INVALID_PARAMETER = -104,

    /** Insufficient memory */
    QUANTIS_ERROR_NO_MEMORY = -105,

    /** No module found or no module active */
    QUANTIS_ERROR_NO_MODULE = -106,

    /** Input/output error */
    QUANTIS_ERROR_IO = -107,

    /** No such device (it may have been disconnected) */
    QUANTIS_ERROR_NO_DEVICE = -108,

    /** Operation not supported or unimplemented */
    QUANTIS_ERROR_OPERATION_NOT_SUPPORTED = -109,

    /** Module status error */
    QUANTIS_ERROR_INVALID_STATUS = -110,

    /** Other error */
    QUANTIS_ERROR_OTHER = -199
  } QuantisError;

  /**
   * Structure representing an handle on a Quantis device. This is an opaque
   * type for which are only ever provided with a pointer, usually originating
   * from QuantisOpen()
   */
  typedef struct QuantisDeviceHandle QuantisDeviceHandle;

  typedef struct QuantisOperations QuantisOperations;

  /**
   *
   */
  struct QuantisDeviceHandle
  {
    int deviceNumber;
    QuantisDeviceType deviceType;
    QuantisOperations *ops;
    void *privateData;
  };

  /**
   *
   */
  struct QuantisOperations
  {
    int (*BoardReset)(QuantisDeviceHandle *deviceHandle);

    void (*Close)(QuantisDeviceHandle *deviceHandle);

    int (*Count)();

    int (*GetBoardVersion)(QuantisDeviceHandle *deviceHandle);

    float (*GetDriverVersion)();

    char *(*GetManufacturer)(QuantisDeviceHandle *deviceHandle);

    int (*GetModulesMask)(QuantisDeviceHandle *deviceHandle);

    int (*GetModulesDataRate)(QuantisDeviceHandle *deviceHandle);

    int (*GetModulesPower)(QuantisDeviceHandle *deviceHandle);

    int (*GetModulesStatus)(QuantisDeviceHandle *deviceHandle);

    char *(*GetSerialNumber)(QuantisDeviceHandle *deviceHandle);

    int (*ModulesDisable)(QuantisDeviceHandle *deviceHandle,
                          int moduleMask);

    int (*ModulesEnable)(QuantisDeviceHandle *deviceHandle,
                         int moduleMask);

    int (*Open)(QuantisDeviceHandle *deviceHandle);

    int (*Read)(QuantisDeviceHandle *deviceHandle,
                void *buffer,
                size_t size);

    int (*GetBusDeviceId)(QuantisDeviceHandle *deviceHandle);

    char *(*QuantisTypeStrError)(int errorNumber);

    int (*GetAis31StartupTestsRequestFlag)(QuantisDeviceHandle *deviceHandle);

    int (*ClearAis31StartupTestsRequestFlag)(QuantisDeviceHandle *deviceHandle);
  };

  /** 
   * Maximal size (in bytes) allowed to be requested at once to QuantisRead call.
   * Increasing the request size minimizes system calls and therefore improve the
   * performance in terms of acquisition speed. To reach the maximum speed 16MiB 
   * should be large enough, but it's highly dependent of the OS and CPU.
   * Please note that if you don't need performance, it is recommended to request 
   * small amount at once (suggested values are between 4KiB and 128KiB) and loop 
   * until all amount of random data has been retrieved.
   */
#define QUANTIS_MAX_READ_SIZE (16 * 1024 * 1024)

  /**
   * Resets the Quantis board.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @return QUANTIS_SUCCESS on success or a QUANTIS_ERROR code on failure.
   * @warning This function do not generally has to be called, since the board
   * is automatically reset.
   */
  DLL_EXPORT int QuantisBoardReset(QuantisDeviceType deviceType,
                                   unsigned int deviceNumber);

  /**
   * Returns the number of specific Quantis type devices that have been detected
   * on the system.
   * @param deviceType specify the type of Quantis device.
   * @return the number of Quantis devices that have been detected on the system.
   * Returns 0 on error or when no card is installed.
   */
  DLL_EXPORT int QuantisCount(QuantisDeviceType deviceType);

  /**
   * Get the version of the board.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @return the version of the board or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisGetBoardVersion(QuantisDeviceType deviceType,
                                        unsigned int deviceNumber);

  /**
   * Returns the version of the driver as a number composed by the 
   * major and minor number: <code>version = major.minor</code>.
   * @param deviceType specify the type of Quantis device.
   * @return the version of the driver or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT float QuantisGetDriverVersion(QuantisDeviceType deviceType);

  /**
   * Returns the library version as a number composed by the major
   * and minor number: <code>version = major.minor</code>
   * @return the library version.
   */
  DLL_EXPORT float QuantisGetLibVersion();

  /**
   * Get a pointer to the manufacturer's string of the Quantis device.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @return the manufacturer of the Quantis device or "Not available"
   * when an error occurred or when the device do not support the operation
   * (currently only Quantis USB returns a valid string).
   */
  DLL_EXPORT char *QuantisGetManufacturer(QuantisDeviceType deviceType,
                                          unsigned int deviceNumber);

  /**
   * Returns the number of modules that have been detected on a Quantis
   * device.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @return the number of detected modules or a QUANTIS_ERROR code on failure.
   * @see QuantisGetModulesMask
   */
  DLL_EXPORT int QuantisGetModulesCount(QuantisDeviceType deviceType,
                                        unsigned int deviceNumber);

  /**
   * Returns the data rate (in Bytes per second) provided by the Quantis device.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @return the data rate provided by the Quantis device or a QUANTIS_ERROR
   * code on failure.
   */
  DLL_EXPORT int QuantisGetModulesDataRate(QuantisDeviceType deviceType,
                                           unsigned int deviceNumber);

  /**
   * Returns a bitmask of the modules that have been detected on a Quantis
   * device, where bit <em>n</em> is set if module <em>n</em> is present.
   * For instance when 5 (1101 in binary) is returned, it means that modules
   * 0, 2 and 3 have been detected.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @return a bitmask of the detected modules or a QUANTIS_ERROR code on failure.
   * @see QuantisGetModulesStatus
   */
  DLL_EXPORT int QuantisGetModulesMask(QuantisDeviceType deviceType,
                                       unsigned int deviceNumber);

  /**
   * Get the power status of the modules.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @return 1 if the modules are powered, 0 if the modules are not powered and
   * a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisGetModulesPower(QuantisDeviceType deviceType,
                                        unsigned int deviceNumber);

  /**
   * Returns the status of the modules on the device as a bitmask as defined 
   * in QuantisGetModulesMask. Bit <em>n</em> is set (equal to 1) only when
   * module <em>n</em> is enabled and functional. 
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @return A bitmask with the status of the modules or a QUANTIS_ERROR code
   * on failure.
   * @see QuantisGetModulesMask
   */
  DLL_EXPORT int QuantisGetModulesStatus(QuantisDeviceType deviceType,
                                         unsigned int deviceNumber);

  /**
   * Get a pointer to the serial number string of the Quantis device.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @return the serial number of the Quantis device or "S/N not available"
   * when an error occurred or when the device do not support the operation
   * (currently only Quantis USB returns a valid serial number).
   */
  DLL_EXPORT char *QuantisGetSerialNumber(QuantisDeviceType deviceType,
                                          unsigned int deviceNumber);

  /**
   * Disable one ore more modules.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param modulesMask a bitmask of the modules (as specified in 
   * QuantisGetModulesMask) that must be disabled.
   * @return QUANTIS_SUCCESS on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisModulesDisable(QuantisDeviceType deviceType,
                                       unsigned int deviceNumber,
                                       int modulesMask);

  /**
   * Enable one ore more modules.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param modulesMask a bitmask of the modules (as specified in 
   * QuantisGetModulesMask) that must be enabled.
   * @return QUANTIS_SUCCESS on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisModulesEnable(QuantisDeviceType deviceType,
                                      unsigned int deviceNumber,
                                      int modulesMask);

  /**
   * Reset one or more modules.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param modulesMask a bitmask of the modules (as specified in 
   * QuantisGetModulesMask) that must be reset.
   * @return QUANTIS_SUCCESS on success or a QUANTIS_ERROR code on failure.
   * @warning This function just call QuantisModulesDisable and then 
   * QuantisModulesEnable with the provided modulesMask.
   */
  DLL_EXPORT int QuantisModulesReset(QuantisDeviceType deviceType,
                                     unsigned int deviceNumber,
                                     int modulesMask);

  /**
   * Retreive the Ais31 Startup Tests Request Flag
   * Ais31 require to perform a startup test once since power up.
   * @param deviceHandle a pointer to a handle the device
   * @return 1 if Startup tests are required, returns 0 if tests are not required
   * otherwise return QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisGetAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle);

  /**
   * Clear the Ais31 Startup Tests Request Flag
   * @param deviceHandle a pointer to a handle the device
   * @return QUANTIS_SUCCESS on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisClearAis31StartupTestsRequestFlag(QuantisDeviceHandle *deviceHandle);

  /**
   * Open the Quantis device.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param deviceHandle a pointer to a pointer to a handle the device
   * @return The number of read bytes on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisOpen(QuantisDeviceType deviceType,
                             unsigned int deviceNumber,
                             QuantisDeviceHandle **deviceHandle);

  /**
   * Close the Quantis device.
   * This function close a previously opened device
   * @param deviceHandle a pointer to a handle the device
   */
  DLL_EXPORT void QuantisClose(QuantisDeviceHandle *deviceHandle);

  /**
   * Reads random data from the Quantis device.
   * This function expect the device has been previously opened
   * @param deviceHandle a pointer to a handle the device
   * @param buffer a pointer to a destination buffer. This buffer MUST 
   * already be allocated. Its size must be at least <em>size</em> bytes.
   * @param size the number of bytes to read (not larger than QUANTIS_MAX_READ_SIZE).
   * @return The number of read bytes on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisReadHandled(QuantisDeviceHandle *deviceHandle,
                                    void *buffer,
                                    size_t size);

  /**
   * Reads random data from the Quantis device.
   * This function perform open read and close
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param buffer a pointer to a destination buffer. This buffer MUST 
   * already be allocated. Its size must be at least <em>size</em> bytes.
   * @param size the number of bytes to read (not larger than QUANTIS_MAX_READ_SIZE).
   * @return The number of read bytes on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisRead(QuantisDeviceType deviceType,
                             unsigned int deviceNumber,
                             void *buffer,
                             size_t size);

  /**
   * Reads a random double floating precision value between 0.0 (inclusive)
   * and 1.0 (exclusive) from the Quantis device.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param value a pointer to a destination value.
   * @return QUANTIS_SUCCESS on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisReadDouble_01(QuantisDeviceType deviceType,
                                      unsigned int deviceNumber,
                                      double *value);

  /**
   * Reads a random single floating precision value between 0.0 (inclusive)
   * and 1.0 (exclusive) from the Quantis device.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param value a pointer to a destination value.
   * @return QUANTIS_SUCCESS on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisReadFloat_01(QuantisDeviceType deviceType,
                                     unsigned int deviceNumber,
                                     float *value);

  /**
   * Reads a random number from the Quantis device.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param value a pointer to a destination value.
   * @return QUANTIS_SUCCESS on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisReadInt(QuantisDeviceType deviceType,
                                unsigned int deviceNumber,
                                int *value);

  /**
   * Reads a random number from the Quantis device.
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param value a pointer to a destination value.
   * @return QUANTIS_SUCCESS on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisReadShort(QuantisDeviceType deviceType,
                                  unsigned int deviceNumber,
                                  short *value);

  /**
   * Reads a random number from the Quantis device and scale it to be between 
   * min (inclusive) and max (exclusive).
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param value a pointer to a destination value.
   * @param min the minimal value the random number can take.
   * @param max the maximal value the random number can take.
   * @return QUANTIS_SUCCESS on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisReadScaledDouble(QuantisDeviceType deviceType,
                                         unsigned int deviceNumber,
                                         double *value,
                                         double min,
                                         double max);

  /**
   * Reads a random number from the Quantis device and scale it to be between
   * min (inclusive) and max (exclusive).
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param value a pointer to a destination value.
   * @param min the minimal value the random number can take.
   * @param max the maximal value the random number can take.
   * @return QUANTIS_SUCCESS on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisReadScaledFloat(QuantisDeviceType deviceType,
                                        unsigned int deviceNumber,
                                        float *value,
                                        float min,
                                        float max);

  /**
   * Reads a random number from the Quantis device and scale it to be between
   * min and max (inclusive).
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param value a pointer to a destination value.
   * @param min the minimal value the random number can take.
   * @param max the maximal value the random number can take.
   * @return QUANTIS_SUCCESS on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisReadScaledInt(QuantisDeviceType deviceType,
                                      unsigned int deviceNumber,
                                      int *value,
                                      int min,
                                      int max);

  /**
   * Reads a random number from the Quantis device and scale it to be between
   * min and max (inclusive).
   * @param deviceType specify the type of Quantis device.
   * @param deviceNumber the number of the Quantis device.
   * @param value a pointer to a destination value.
   * @param min the minimal value the random number can take.
   * @param max the maximal value the random number can take.
   * @return QUANTIS_SUCCESS on success or a QUANTIS_ERROR code on failure.
   */
  DLL_EXPORT int QuantisReadScaledShort(QuantisDeviceType deviceType,
                                        unsigned int deviceNumber,
                                        short *value,
                                        short min,
                                        short max);

  /**
   * Get a pointer to the error message string.
   *
   * This functions interprets the value of errorNumber and generates a string
   * describing the error.
   *
   * The returned pointer points to a statically allocated string, which shall
   * not be modified by the program. Further calls to this function will
   * overwrite its content.
   *
   * @param errorNumber The error number.
   * @return A pointer to the error message string.
   */
  DLL_EXPORT char *QuantisStrError(QuantisError errorNumber);

  DLL_EXPORT char *QuantisFullStrError(QuantisDeviceType deviceType, QuantisError errorNumber);

#ifdef __cplusplus
}
#endif

#endif /* QUANTIS_H */
