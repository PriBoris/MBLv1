
#include "LightTemperature.h"

#include "Ports.h"


#define SDA_GPIO_PIN	GPIOB, 7
#define SCL_GPIO_PIN	GPIOB, 8

#define SDA_AF		Ports::GPIO_AF1
#define SCL_AF		Ports::GPIO_AF4



void LightTemperature::init(){



	setPortsGPI();
	
	RCC->CCIPR |= 
		(0*RCC_CCIPR_I2C1SEL_0) |
		(0*RCC_CCIPR_I2C1SEL_1) | //APB1 clock sources I2C peripheral
		0;
	
}

void LightTemperature::start(uint32_t apbClockHz){
	
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	setPortsI2C();


}

void LightTemperature::stop(void){


	setPortsGPI();
	RCC->APB1ENR &= ~RCC_APB1ENR_I2C1EN;


}


void LightTemperature::setPortsI2C(){

	Ports::initAlternate(
		SDA_GPIO_PIN,
		SDA_AF,
		Ports::GPIO_OpenDrain,
		Ports::GPIO_MediumSpeed,
		Ports::GPIO_NoPull
		);	

	Ports::initAlternate(
		SCL_GPIO_PIN,
		SCL_AF,
		Ports::GPIO_OpenDrain,
		Ports::GPIO_MediumSpeed,
		Ports::GPIO_NoPull
		);
}

void LightTemperature::setPortsGPI(){

	Ports::initInput(
		SDA_GPIO_PIN,
		Ports::GPIO_NoPull
		);	

	Ports::initInput(
		SCL_GPIO_PIN,
		Ports::GPIO_NoPull
		);	

}

extern "C"{void I2C1_IRQHandler(){
	
}}


/*

hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00303D5B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

*/
