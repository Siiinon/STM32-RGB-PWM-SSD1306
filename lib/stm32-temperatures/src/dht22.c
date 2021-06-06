
#include "dht22.h"

#if defined(DHT22_ENABLED)

void DHT22_Start(void) {

	Set_Pin_Output(DHT22_PORT, DHT22_PIN); // set the pin as output
	HAL_GPIO_WritePin(DHT22_PORT, DHT22_PIN, 0);   // pull the pin low
	delay(1200);   // wait for > 1ms

	HAL_GPIO_WritePin (DHT22_PORT, DHT22_PIN, 1);   // pull the pin high
	delay(20);   // wait for 30us

	Set_Pin_Input(DHT22_PORT, DHT22_PIN);   // set as input

}

uint8_t DHT22_Check_Response(void) {

  uint8_t response = 0;

	Set_Pin_Input(DHT22_PORT, DHT22_PIN);   // set as input
	
	delay(40);  // wait for 40us
	if (!(HAL_GPIO_ReadPin (DHT22_PORT, DHT22_PIN))) { // if the pin is low
	
		delay(80);   // wait for 80us

    response = HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN) ? 1 : -1;  // if the pin is high, response is ok

	}

	while ((HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN)));   // wait for the pin to go low

	return response;

}

uint8_t DHT22_Read(void) {

	uint8_t i, j;

	for(j=0; j<8; j++) {

		while (!(HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN)));   // wait for the pin to go high
		delay(40);   // wait for 40 us

		if(!(HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN))) {   // if the pin is low
			i&= ~(1<<(7-j));   // write 0
		} else {
		  i|= (1<<(7-j));  // if the pin is high, write 1
    } 

		while ((HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN)));  // wait for the pin to go low

	}

	return i;
  
}

void dht22_Get_Temperature_Humidity(float *temperature, float *humidity) {

    uint8_t temperature_byte1, temperature_byte2, humidity_byte1, humidity_byte2;
    uint16_t temp_temperature, temp_humidity; 

	  DHT22_Start();
	  DHT22_Check_Response();
	  humidity_byte1 = DHT22_Read();
    humidity_byte2 = DHT22_Read();
	  temperature_byte1 = DHT22_Read();
	  temperature_byte2 = DHT22_Read();
	  DHT22_Read();

	  temp_temperature = (temperature_byte1 << 8) | temperature_byte1;
	  temp_humidity = (humidity_byte1 << 8) | humidity_byte2;

	  *temperature = (float) (temp_temperature / 10.0);
	  *humidity = (float) (temp_humidity / 10.0);

}

#endif