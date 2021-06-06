
#include "ds18b20.h"

void delay(uint16_t time) {
	
  __HAL_TIM_SET_COUNTER(&DS18B20_TIMER, 0);
  while ((__HAL_TIM_GET_COUNTER(&DS18B20_TIMER))<time);

}

void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

}

void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

}

uint8_t DS18B20_Start(void) {

	Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);   // set the pin as output
	HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);  // pull the pin low
	delay(480);   // delay according to datasheet

	Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);    // set the pin as input
	delay(80);    // delay according to datasheet

  uint8_t response = HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN) ? -1 : 1;

	delay(400); // 480 us delay totally.

	return response;

}

void DS18B20_Write(uint8_t data) {

	Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);  // set as output

	for(int i=0; i<8; i++) {

		if((data & (1<<i)) != 0) { // if the bit is high
		
			// write 1

			Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);  // set as output
			HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);  // pull the pin LOW
			delay(1);  // wait for 1 us

			Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);  // set as input
			delay(50);  // wait for 60 us

		} else { // if the bit is low
		
			// write 0

			Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);
			HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);  // pull the pin LOW
			delay(50);  // wait for 60 us

			Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);

		}
	}
}

uint8_t DS18B20_Read(void) {

	uint8_t value = 0;

	Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);

	for (int i=0;i<8;i++) {

		Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);   // set as output

		HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);  // pull the data pin LOW
		delay(1);  // wait for > 1us

		Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);  // set as input
		if (HAL_GPIO_ReadPin (DS18B20_PORT, DS18B20_PIN)) {  // if the pin is HIGH
			value |= 1<<i;  // read = 1
		}
    
		delay (50);  // wait for 60 us
	}

	return value;
  
}

void ds18b20_Get_Temperature(float *temperature) {

  uint8_t temp_byte1, temp_byte2;
  uint16_t temp; 

  DS18B20_Start();
	HAL_Delay(1);
	DS18B20_Write(0xCC);  // skip ROM
	DS18B20_Write(0x44);  // convert t
	HAL_Delay(800);

	DS18B20_Start();
  HAL_Delay(1);
  DS18B20_Write(0xCC);  // skip ROM
  DS18B20_Write(0xBE);  // Read Scratch-pad

  temp_byte1 = DS18B20_Read();
	temp_byte2 = DS18B20_Read();
	temp = (temp_byte2 << 8) | temp_byte1;

	*temperature = (float) temp / 16;

}
