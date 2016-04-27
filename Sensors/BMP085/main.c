
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
/* I2C handler declaration */
I2C_HandleTypeDef hi2c3;

/* Variables for temperature and pressure */
float BMP085_temp_K;
long BMP085_press_K;
char stringPrint[30];

int main(void) {
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C3_Init();
	BSP_LED_Init(LED4);

	/* Initialize the LCD */
  BSP_LCD_Init();
  /* Initialize TS on whole screen */
  BSP_TS_Init(240, 360);
	
  /* Select Layer */
  BSP_LCD_LayerDefaultInit(1, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer(1);
	
  BSP_LCD_DisplayOn();
  /* LCD background color */
  BSP_LCD_Clear(LCD_COLOR_LIGHTBLUE);
  /* Text background color */
  BSP_LCD_SetBackColor(LCD_COLOR_LIGHTBLUE);
  /* Text color */
  BSP_LCD_SetTextColor(LCD_COLOR_RED);

  /* BMP calibration */
  BMP085Calibration(&hi2c3);
	
  while (1) {
		DefaultDraw();
		TouchDifference();
  }
}

/** System Clock Configuration
*/
void SystemClock_Config(void) {

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  HAL_PWREx_ActivateOverDrive();

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
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

/* Pinout Configuration */
void MX_GPIO_Init(void) {
  /* GPIO Ports Clock Enable */
  __GPIOC_CLK_ENABLE();
  __GPIOA_CLK_ENABLE();
}
/**
* @brief Draws initial screen
* @param None
* @retval None
*/
static void DefaultDraw(void) {
	
	BSP_LCD_DisplayStringAt(0, 40, "scaluza.com", CENTER_MODE);
	
	/* 1st button */
	BSP_LCD_DrawRect(10, 245, 80, 70);
	BSP_LCD_DisplayStringAt(30, 270, "ON", LEFT_MODE);
	
	/* 2rd button */
	BSP_LCD_DrawRect(150, 245, 80, 70);
	BSP_LCD_DisplayStringAt(220, 270, "OFF", RIGHT_MODE);
}
 
/**
* @brief Checks if screen was touched
* @param None
* @retval None
*/
 static void TouchDifference(void) {
	
	static TS_StateTypeDef  TS_State;
	static uint32_t x = 0, y = 0;
		
	/* Get touch screen position */
	BSP_TS_GetState(&TS_State);
	x = TS_State.X;
	y = TS_State.Y;
	
	/* Checks if touch is detected */
	if(TS_State.TouchDetected){
		
		/* All buttons are located in same Y area
		 * Y axis only needs to be checked once
		 */
		if(y > 245 & y < 315) {
			
			/* Checks if 1st button is pressed */
			if(x > 10 & x < 90) {
			
				BSP_LCD_SetTextColor(LCD_COLOR_RED);
				BSP_LCD_DisplayStringAt(0, 100, "Temperature", CENTER_MODE);
				BSP_LCD_DisplayStringAt(0, 160, "Pressure", CENTER_MODE);
				
				BMP085_temp_K = BMP085calculateTemperature(BMP085readUT(&hi2c3));
				/* Calculating temperature value */
				BMP085_temp_K = BMP085_temp_K * 0.1;
				/* Output to LCD */
				sprintf(stringPrint, "%.1f", BMP085_temp_K);
				BSP_LCD_DisplayStringAt(0, 120, stringPrint, CENTER_MODE);
 
				/* Pressure */
				BMP085_press_K = BMP085calculatePressure(BMP085readUP(&hi2c3));
				/* Output to LCD */
				sprintf(stringPrint, "%ld", BMP085_press_K);
				BSP_LCD_DisplayStringAt(0, 180, stringPrint, CENTER_MODE);		
			}
			
			else if(x > 150 & x < 240) {
				/* LCD background color */
				BSP_LCD_Clear(LCD_COLOR_LIGHTBLUE);
			}
		}
	}
}

