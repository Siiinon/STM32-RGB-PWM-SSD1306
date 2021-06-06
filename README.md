# STM32-RGB-PWM-SSD1306
## STM32 Project to control RGB LED with PWM and showing color values on SSD1306 display via I2C


This goal of this project is to explore some concepts of STM32 MCU.
Some of the features explored in this project are:

- Control RGB LED via PWM
- Use ADC with Timers via DMA (to read 10K Potentiometer)
- Control SSD1306 (128x64) via I2C
- Interface with PUSH buttons via hardware interrupts
- Reading Temperature using DS128B20 sensor

#

The base project was created with STM32CubeMX and then exported and worked in PlatformIO.

The project is defined to work on STM32F411CEU6 chip thats comes in in well know Blackpill board. But it can be easily modified to work in another STM32 chips.

Feedback for improvements or corrections are welcomed :)