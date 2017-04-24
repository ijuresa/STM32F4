/*******************************************************************************
* Copyright (C) 2017, Ivan Juresa
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*******************************************************************************/

#ifndef SERIAL_DEBUG_H
#define SERIAL_DEBUG_H

#define SERIAL_DEBUG_TIMEOUT 	0xFFFFu
#define SERIAL_MODE_LEN			0x2u
#define SERIAL_MODE_POLLING		0x0u
#define SERIAL_MODE_INTERRUPT	0x1u

/* Includes */
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdbool.h>


#ifdef SERIAL_DEBUG_C
	static void serialDebug_write(const char *inputString, uint8_t sendMode); 
	static void serialDebug_read(const char *inputString); 
	static void serialDebug_close();
#endif

void INIT_serial(UART_HandleTypeDef *huart);

typedef struct serialDebug_STRUCT {
	UART_HandleTypeDef *huart;
	_Bool enabled;
	
	void (*write)(const char * ,uint8_t );
	void (*read)(const char *);
	void (*close)();
} serialDebug_S;

extern serialDebug_S Serial;
#endif // SERIAL_DEBUG
