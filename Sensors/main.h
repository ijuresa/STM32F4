
#ifndef __MAIN_H__
#define __MAIN_H__

 /* Includes */
 #include "stm32f4xx_hal.h"
 #include "stm32f429i_discovery.h"
 #include "stm32f429i_discovery_lcd.h"
 #include "stm32f429i_discovery_ts.h"
 #include "BMP085.h"

 /* Private function prototypes -----------------------------------------------*/
 void SystemClock_Config(void);
 static void MX_GPIO_Init(void);
 static void MX_I2C3_Init(void);
 static void DefaultDraw(void);
 static void TouchDifference(void);

 

 #endif		//__MAIN_H__