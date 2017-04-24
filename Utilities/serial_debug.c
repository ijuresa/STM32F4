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
#ifndef SERIAL_DEBUG_C
#define SERIAL_DEBUG_C

/* Includes */
#include "serial_debug.h"

serialDebug_S Serial = {
	.huart 		= 0,
	.enabled 	= false,
};

/* Override - callback when message is transmitted */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	
}


void INIT_serial(UART_HandleTypeDef *huart) {
	Serial.huart = huart;
	Serial.close = serialDebug_close;
	Serial.write = serialDebug_write;
	Serial.read  = serialDebug_read;
	
	Serial.enabled = true;
}

static void serialDebug_write(const char *inputString, uint8_t sendMode) {
	assert_param(sendMode <= SERIAL_MODE_LEN);
	assert_param(sendModee >= NULL);
	
	if(sendMode == SERIAL_MODE_POLLING) {
		HAL_UART_Transmit(Serial.huart, (uint8_t *)inputString, 
							strlen(inputString), SERIAL_DEBUG_TIMEOUT);
	} else {
		HAL_UART_Transmit_IT(Serial.huart, (uint8_t *)inputString, 
							strlen(inputString));
	}
	
	if(Serial.huart->ErrorCode != HAL_OK) {
		// TODO: Error handle
	}
}	

static void serialDebug_read(const char *inputString) {
	
}

static void serialDebug_close() {
	
	
}

#endif // SERIAL_DEBUG
