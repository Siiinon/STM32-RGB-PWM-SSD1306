
#ifndef __STM32_TEMPERATURES_CONF_H__
#define __STM32_TEMPERATURES_CONF_H__

#define STM32F4
#define TEMPS_TIMER htim1

// #define DS18B20_ENABLED
#if defined(DS18B20_ENABLED)
#define DS18B20_PORT GPIOA
#define DS18B20_PIN GPIO_PIN_3
#endif

// #define DHT22_ENABLED
#if defined(DHT22_ENABLED)
#define DHT22_PORT GPIOA
#define DHT22_PIN GPIO_PIN_4
#endif

#endif