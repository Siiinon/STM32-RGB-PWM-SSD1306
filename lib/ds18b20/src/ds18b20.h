/**
 * Library to interface with one-wire temperature sensor DS18B20.
 * This library requires a Timer where every count takes 1us (microsecond).
 * 
 * This library was developed by ControllersTech (https://controllerstech.com/).
 * Some small refactoring was done organize this code as a library.
 * 
 * Source: https://controllerstech.com/ds18b20-and-stm32/ 
 */

#ifndef __DS18B20_H__
#define __DS18B20_H__

#include <stddef.h>
#include <_ansi.h>

_BEGIN_STD_C

#include "ds18b20_conf.h"

#if defined(STM32F4)
#include "stm32f4xx_hal.h"
#else
#error "DS18B12 library was tested only on STM32F4 MCU families!"
#endif

#ifndef DS18B20_TIMER
#define DS18B20_TIMER htim1
#endif 

#ifndef DS18B20_PORT
#define DS18B20_PORT GPIOA
#endif 

#ifndef DS18B20_PIN
#define DS18B20_PIN GPIO_PIN_3
#endif

extern TIM_HandleTypeDef DS18B20_TIMER;

void ds18b20_Get_Temperature(float *temperature);

_END_STD_C

#endif