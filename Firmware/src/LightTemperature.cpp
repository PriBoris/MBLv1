
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



