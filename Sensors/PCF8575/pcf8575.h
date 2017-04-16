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
 
#ifndef __PCF8575_H__
#define __PCF8575_H__

 /* Includes */
#include "stm32f4xx_hal.h"
 
/*******************************************************************************
* @brief  	Initializes PCF8575 write and read address
********************************************************************************
* @param  	readAddress: PCF8575 read address
* @param		writeAddress: PCF8575 write address
* @retval	Nothing
*******************************************************************************/
void PCF8575_Init(uint8_t readAddress, uint8_t writeAddress);
 
/*******************************************************************************
* @brief  	All outputs goes low
********************************************************************************
* @note		All pins are set as OUTPUT
* @param  	*I2CxHandle: Pointer to I2C which is used
* @retval	Nothing
*******************************************************************************/
void PCF8575_Clear(I2C_HandleTypeDef *I2CxHandle);

/*******************************************************************************
* @brief  	All outputs goes high
********************************************************************************
* @note		All pins are set as INPUTS		
* @param  	*I2CxHandle: Pointer to I2C which is used
* @retval	Nothing
*******************************************************************************/
void PCF8575_Set(I2C_HandleTypeDef *I2CxHandle);

/*******************************************************************************
* @brief  	Reads pins
********************************************************************************
* @param  	*I2CxHandle: Pointer to I2C which is used
* @retval	16bit data
*******************************************************************************/
int PCF8575_Read(I2C_HandleTypeDef *I2CxHandle);
 
/*******************************************************************************
* @brief  	Setting pins as input or output
********************************************************************************
* @param  	*I2CxHandle: Pointer to I2C which is used
* @param  	data: value of pins 
* @retval	Nothing
*******************************************************************************/
void PCF8575_Write(I2C_HandleTypeDef *I2CxHandle, int data);
 
 #endif   // __PCF8575_H__
 