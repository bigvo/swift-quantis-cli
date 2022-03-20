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

#include <string.h>

#ifdef _MSC_VER
#include "msc_stdint.h"
#else
#include <stdint.h>
#endif

#include "Conversion.h"

double ConvertToDouble_01(const char *buffer)
{
  uint64_t value;
  memcpy(&value, buffer, sizeof(value));
  return (double)value / ((double)0xFFFFFFFFFFFFFFFFull + 1.0);
}

float ConvertToFloat_01(const char *buffer)
{
  uint32_t value;
  memcpy(&value, buffer, sizeof(value));
  return (float)value / ((float)0xFFFFFFFFu + 1.0f);
}

int ConvertToInt(const char *buffer)
{
  int value;
  memcpy(&value, buffer, sizeof(value));
  return value;
}

short ConvertToShort(const char *buffer)
{
  short value;
  memcpy(&value, buffer, sizeof(value));
  return value;
}

char ConvertHexaToByte(char c)
{
  if ('0' <= c && c <= '9')
    return c - '0';
  if ('a' <= c && c <= 'f')
    return c - 'a' + 10;
  return 0;
}

void ConvertByteToHexa(unsigned char h, char *c)
{
  unsigned char i = h / 0x10;
  if (i < 10)
    c[0] = i + '0';
  else
    c[0] = (i - 0xa) + 'a';

  i = h % 0x10;
  if (i < 10)
    c[1] = i + '0';
  else
    c[1] = (i - 0xa) + 'a';
}

void ConvertHexaToByteArray(unsigned char *data, const char *text, size_t length)
{
  size_t i = 0;

  for (i = 0; i < length; ++i)
  {
    data[i] = (ConvertHexaToByte(text[i * 2]) << 4) + ConvertHexaToByte(text[(i * 2) + 1]);
  }
}

void ConvertByteArrayToHexa(char *string, unsigned char *data, size_t length)
{
  size_t i = 0;

  for (i = 0; i < length; ++i)
  {
    ConvertByteToHexa(data[i], string + (i * 2));
    string[(i * 2) + 2] = '\0';
  }
  string[length * 2] = '\0';
}
