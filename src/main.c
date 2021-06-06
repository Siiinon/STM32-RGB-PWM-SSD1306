#include "main.h"
#include "dma.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"
#include "ssd1306.h"
#include "ds18b20.h"
#include <stdio.h>

void SystemClock_Config(void);
void Print_Core_Freq(void);
void Set_RGB_LED(void);
void Display_RGB_Values(void);
void Set_Color_ADC(void);
void Display_Temperature(void);
void Measure_Temperature(void);

uint32_t rgb[3];
uint32_t color_selector = 0;
uint32_t adc_data[1];
float temperature;
u_int8_t measure_temperature = 0;

int main(void) {

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_ADC1_Init();

  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_Base_Start(&htim3);
  HAL_TIM_Base_Start_IT(&htim4);

  HAL_ADC_Start_DMA(&hadc1, adc_data, 1);

  ssd1306_Init();
  ssd1306_Fill(Black);

  Print_Core_Freq();

  while (1) {

    Set_Color_ADC();
    Set_RGB_LED();
    Display_RGB_Values();
    Measure_Temperature();

    HAL_Delay(1);

  }
  
}

void Print_Core_Freq(void) {
  char buffer[32];
  sprintf(buffer, "Core Freq: %luMHz", HAL_RCC_GetHCLKFreq() / 1000000);
  ssd1306_SetCursor(2, 0);
  ssd1306_WriteString(buffer, Font_7x10, White);
  ssd1306_UpdateScreen();
}

void Set_RGB_LED(void) {
  htim1.Instance->CCR2 = rgb[0];
  htim1.Instance->CCR3 = rgb[1];
  htim1.Instance->CCR4 = rgb[2];
}

void Set_Color_ADC(void) {
  rgb[color_selector - 1] = adc_data[0];
}

void Display_RGB_Values(void) {

  char buffer[7];

  sprintf(buffer, "R:%03lu", rgb[0]);
  ssd1306_SetCursor(2, 15);
  ssd1306_WriteString(buffer, Font_7x10, color_selector == 1 ? Black : White);
  ssd1306_WriteString("|", Font_7x10, White);

  sprintf(buffer, "G:%03lu", rgb[1]);
  ssd1306_WriteString(buffer, Font_7x10, color_selector == 2 ? Black : White);
  ssd1306_WriteString("|", Font_7x10, White);

  sprintf(buffer, "B:%03lu", rgb[2]);
  ssd1306_WriteString(buffer, Font_7x10, color_selector == 3 ? Black : White);

  ssd1306_UpdateScreen();

}

void Measure_Temperature(void) {

  if (measure_temperature) {
    ds18b20_Get_Temperature(&temperature);
    Display_Temperature();
    measure_temperature = 0;
  }

}

void Display_Temperature(void) {

  char buffer[16];

  sprintf(buffer, "Temp 1: %.1fC", temperature);
  ssd1306_SetCursor(2, 25);
  ssd1306_WriteString(buffer, Font_7x10, White);
  ssd1306_UpdateScreen();
  
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

  if (GPIO_Pin == GPIO_PIN_0) {

    color_selector++;
    if(color_selector > 3) {
      color_selector = 0;
    }

  } else {
    __NOP();
  }

}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

  if(htim == &htim4) {
    measure_temperature = 1;
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
  }

}

void SystemClock_Config(void) {

  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
    Error_Handler();
  }

}

void Error_Handler(void) {

  __disable_irq();

  while (1) {

  }

}
