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

#include "stm32_temperatures_common.h"

#if defined(DS18B20_ENABLED)

#ifndef DS18B20_PORT
#define DS18B20_PORT GPIOA
#endif 

#ifndef DS18B20_PIN
#define DS18B20_PIN GPIO_PIN_3
#endif

void ds18b20_Get_Temperature(float *temperature);

#endif

_END_STD_C

#endif