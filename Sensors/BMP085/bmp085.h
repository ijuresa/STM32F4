
/**
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
**/

 #ifndef __BMP085_H__
 #define __BMP085_H__
 
 #include "stm32f4xx_hal.h"

 /**
 * @brief  	Calculates calibration values
 * @param  	*I2CxHandle: Pointer to I2C which is used
 * @retval	None
 **/
 void BMP085Calibration(I2C_HandleTypeDef *I2CxHandle);
 
 
 /**
 * @brief  Reads 16 bit calibration coeficients from E2PROM data
 * @param  *I2CxHandle: Pointer to I2C which is used
 * @param  address: Address of parameters MSB registers
 * @retval Value from E2PROM registers
 **/
 int BMP085readCalibration(I2C_HandleTypeDef *I2CxHandle, uint8_t address);
 
 
 /**
 * @brief  Reads uncompensated temperature value
 * @param  *I2CxHandle: Pointer to I2C which is used
 * @retval UT: Uncompensated temperature value
 **/
 int BMP085readUT(I2C_HandleTypeDef *I2CxHandle);
 
 
 /**
 * @brief  Calculates temperature value
 * @param  ut: Uncompensated temperature value
 * @retval Temperature value
 **/
 int BMP085calculateTemperature(long ut);
 
 
 /**
 * @brief  Reads uncompensated pressure value(UP)
 * @param  *I2CxHandle: Pointer to I2C which is used
 * @retval up: Uncompensated pressure value
 **/
 int BMP085readUP(I2C_HandleTypeDef *I2CxHandle);
 
 
 /**
 * @brief  Calculate pressure value
 * @param  up: Uncompensated pressure value
 * @retval Pressure value
 **/
 int BMP085calculatePressure(long up);
 
 
 #endif   // __BMP085_H__

