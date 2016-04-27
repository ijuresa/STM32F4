
/* 
 * Example1: 
 * PIR (Passive Infrared Sensor) is connected to PD17 on PCF8575
 * PD17 is set as input (1)
 * When motion is detected it sets pin high
 * In while() loop PCF8575 detects it, and sets PG14 LED
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c3;

/* Private function prototypes -----------------------------------------------*/
uint16_t PCF1 = 0x0000;

int main(void) {
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C3_Init();
	
	/* Sending Address*/
	PCF8575_Init(0x41, 0x40);
	
	/* Setting PD17 as INPUT(1) */
  PCF8575_Write(&hi2c3, 0x8000);

  while (1) {
		/*Checks if PD17 is pulled high */
		if((PCF1 = PCF8575_Read(&hi2c3)) == 0x8000) {
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
		}
  }
}

/* I2C3 init function */
void MX_I2C3_Init(void) {
  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
  HAL_I2C_Init(&hi2c3);
}
