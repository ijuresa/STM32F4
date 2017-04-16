/*******************************************************************************
* Copyright (C) 2016, Ivan Juresa
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

/* Includes */
#include "pcf8575.h"

/* Read and write address */
uint8_t array[2];

void PCF8575_Init(uint8_t readAddress, uint8_t writeAddress) {
	array[0] = readAddress;
	array[1] = writeAddress;
}

void PCF8575_Clear(I2C_HandleTypeDef *I2CxHandle) {
	uint8_t output[2];
	output[0] = 0x00;
	output[1] = 0x00;
	
	HAL_I2C_Master_Transmit(I2CxHandle, (uint16_t)array[1], output, 2, 1000);
}

void PCF8575_Set(I2C_HandleTypeDef *I2CxHandle) {
	uint8_t output[2];
	output[0] = 0xFF;
	output[1] = 0xFF;
	
	HAL_I2C_Master_Transmit(I2CxHandle, (uint16_t)array[1], output, 2, 1000);
}

int PCF8575_Read(I2C_HandleTypeDef *I2CxHandle) {
	uint8_t input[2];
	
	HAL_I2C_Master_Receive(I2CxHandle, (uint16_t)array[0], input, 2, 1000);	
	
	return ((input[1] << 8) | input[0]);
}

void PCF8575_Write(I2C_HandleTypeDef *I2CxHandle, int data) {
	uint8_t output[2];
	output[0] = data;
	output[1] = data >> 8;
	
	HAL_I2C_Master_Transmit(I2CxHandle, (uint16_t)array[1], output, 2, 1000);
}
