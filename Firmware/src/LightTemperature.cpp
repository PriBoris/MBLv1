
#include "LightTemperature.h"

#include "Ports.h"

#include <string.h>

#define SDA_GPIO_PIN	GPIOB, 7
#define SCL_GPIO_PIN	GPIOB, 8

#define SDA_AF		Ports::GPIO_AF1
#define SCL_AF		Ports::GPIO_AF4


uint8_t LightTemperature::dataBuffer[LightTemperature::DATA_BUFFER_LENGTH];
uint32_t LightTemperature::actualTransferLength;
bool LightTemperature::transferComplete;
uint32_t LightTemperature::transferCount;


void LightTemperature::init(){

	memset(dataBuffer, 0, sizeof(dataBuffer));
	transferCount = 0;
	transferComplete = false;
	actualTransferLength = 0;

	setPortsGPI();
	
	RCC->CCIPR |= 
		(0*RCC_CCIPR_I2C1SEL_0) |
		(0*RCC_CCIPR_I2C1SEL_1) | //APB1 clock sources I2C peripheral
		0;
	
}

void LightTemperature::start(uint32_t apbClockHz){
	
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;


	I2C1->TIMINGR = 
		(0x0 << 28) + // Timing prescaler
		(0x3 << 20) + // Data setup time
		(0x0 << 16) + // Data hold time
		(0x3D << 8) + // SCL high period (master mode)
		(0x5B << 0) + // SCL low period (master mode)
		0;

	I2C1->OAR1 = 0;
	I2C1->OAR2 = 0;


	I2C1->CR2 = 0;

	I2C1->CR1 = 
		(1 << 7) + // Error interrupts enable
		(1 << 6) + // Transfer Complete interrupt enable 
		(1 << 5) + // STOP detection Interrupt enable
		(1 << 4) + // Not acknowledge received Interrupt enable 
		(1 << 2) + // RX Interrupt enable
		(1 << 1) + // TX Interrupt enable
		(1 << 0) + // Peripheral enable
		0;

	NVIC_ClearPendingIRQ(I2C1_IRQn);
	NVIC_EnableIRQ(I2C1_IRQn);

	setPortsI2C();


}

void LightTemperature::stop(void){


	NVIC_DisableIRQ(I2C1_IRQn);
	setPortsGPI();

	
	I2C1->CR1 = 0;	
	
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
	LightTemperature::isr();
}}

void LightTemperature::isr(void){

	__asm("	nop");
	
	if (I2C1->ISR & I2C_ISR_NACKF){

		I2C1->ICR = I2C_ICR_NACKCF;

	}else if (I2C1->ISR & I2C_ISR_STOPF){

		I2C1->ICR = I2C_ICR_STOPCF;
		transferComplete = true;
		transferCount++;

	}else if (I2C1->ISR & I2C_ISR_ARLO){

		I2C1->ICR = I2C_ICR_ARLOCF;
		
	}else if (I2C1->ISR & I2C_ISR_TC){

		I2C1->CR2 |= I2C_CR2_STOP;

	}else if (I2C1->ISR & I2C_ISR_RXNE){

		dataBuffer[actualTransferLength++] = I2C1->RXDR;

	}else{

		__asm("	nop");

	}



}



uint8_t LightTemperature::getSlaveAddress(uint8_t channel){

	if (channel == CHANNEL_LEFT){
		return (LM75A::AddressBase + 0);
	}else{
		return (LM75A::AddressBase + 1);
	}

}


int8_t LightTemperature::readTemperature(uint8_t channel){

	uint8_t sensorAddress = getSlaveAddress(channel);

	uint8_t transferLength = 2;

	I2C1->CR2 = 
		(sensorAddress << (I2C_CR2_SADD_Pos+1)) + 
		(1 << I2C_CR2_RD_WRN_Pos) + // Master requests a read transfer.
		(transferLength << I2C_CR2_NBYTES_Pos) + // Number of bytes
		0;

	actualTransferLength = 0;
	transferComplete = false;


	I2C1->CR2 |= I2C_CR2_START;

	while(transferComplete == false){
		__asm(" nop");
	}
	
	if (actualTransferLength == transferLength){

		
		return *(int8_t*)&dataBuffer[0]; // integer part
	}else{
		
		return ERROR_VALUE;
	}
	
	
/*



*/	



	
}



