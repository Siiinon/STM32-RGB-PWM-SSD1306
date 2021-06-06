#ifndef __STM32_TEMPERATURES_COMMON_H__
#define __STM32_TEMPERATURES_COMMON_H__

#include "stm32_temperatures_conf.h"

#include <stddef.h>
#include <_ansi.h>

_BEGIN_STD_C

#if defined(STM32F4)
#include "stm32f4xx_hal.h"
#else
#error "STM32 Temperatures Library library was tested only on STM32F4 MCU families!"
#endif

extern TIM_HandleTypeDef TEMPS_TIMER;

void delay(uint16_t time);
void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

_END_STD_C

#endif