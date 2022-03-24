/*
 * Conversion functions
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

#ifndef QUANTIS_CONVERSION_H
#define QUANTIS_CONVERSION_H

#ifdef _MSC_VER
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#include <stddef.h>

#include "DllMain.h"

#ifdef __cplusplus
extern "C"
{
#endif

  /**
   * Convert a C string to a double value between 0.0 (inclusive) and 1.0 (exclusive).
   * @param buffer the buffer (at sizeof(double) long) to convert.
   * @return a double value between 0.0 (inclusive) and 1.0 (exclusive).
   * @note only the significand is filled with random bits.
   */
  DLL_EXPORT double ConvertToDouble_01(const char *buffer);

  /**
   * Convert a C string to a float value between 0.0 (inclusive) and 1.0 (exclusive).
   * @param buffer the buffer (at least sizeof(float) long) to convert.
   * @return a float value between 0.0 (inclusive) and 1 (exclusive).
   * @note only the significand is filled with random bits.
   */
  DLL_EXPORT float ConvertToFloat_01(const char *buffer);

  /**
   * Convert a C string to a int value.
   * @param buffer the buffer (at least sizeof(int) long) to convert.
   * @return a int value.
   */
  DLL_EXPORT int ConvertToInt(const char *buffer);

  /**
   * Convert a C string to a short value.
   * @param buffer the buffer (at least sizeof(short) long) to convert.
   * @return a short value.
   */
  DLL_EXPORT short ConvertToShort(const char *buffer);

  /**
   * Convert a hexadecimal character to a byte.
   * @param c the character to convert.
   * @return a byte.
   */
  DLL_EXPORT char ConvertHexaToByte(char c);

  /**
   * Convert a byte to a hexadecimal string.
   * @param h the byte to convert.
   * @param c the hexadecimal string.
   */
  DLL_EXPORT void ConvertByteToHexa(unsigned char h, char *c);

  /**
   * Convert a hexadecimal string to a byte array.
   * @param data the byte buffer to fill.
   * @param text the hexadecimal string to convert.
   * @param length number of byte to convert.
   */
  DLL_EXPORT void ConvertHexaToByteArray(unsigned char *data, const char *text, size_t length);

  /**
   * Convert a byte array to a hexadecimal string.
   * @param string the hexadecimal string to fill.
   * @param data the byte buffer to convert.
   * @param length number of byte to convert.
   */
  DLL_EXPORT void ConvertByteArrayToHexa(char *string, unsigned char *data, size_t length);

#ifdef __cplusplus
}
#endif

#endif /*  QUANTIS_CONVERSION_H */
