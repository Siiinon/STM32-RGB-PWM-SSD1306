/**
 * Library to interface with one-wire temperature sensor DHT22.
 * This library requires a Timer where every count takes 1us (microsecond).
 * 
 * This library was developed by ControllersTech (https://controllerstech.com/).
 * Some small refactoring was done organize this code as a library.
 * 
 * Source: https://controllerstech.com/ds18b20-and-stm32/ 
 */

#ifndef __DHT22_H__
#define __DHT22_H__

#include "stm32_temperatures_common.h"

_BEGIN_STD_C

#if defined(DHT22_ENABLED)

#ifndef DHT22_PORT
#define DHT22_PORT GPIOA
#endif 

#ifndef DHT22_PIN
#define DHT22_PIN GPIO_PIN_4
#endif

void dht22_Get_Temperature_Humidity(float *temperature, float *humidity);

#endif

_END_STD_C

#endif