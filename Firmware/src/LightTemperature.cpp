
#include "LightTemperature.h"

#include "Ports.h"

#include <string.h>

#define SDA_GPIO_PIN	GPIOB, 7
#define SCL_GPIO_PIN	GPIOB, 8

#define SDA_AF		Ports::GPIO_AF1
#define SCL_AF		Ports::GPIO_AF4


uint8_t LightTemperature::transferData[LightTemperature::TRANSFER_DATA_BUFFER_LENGTH];
uint32_t LightTemperature::actualTransferLength;
bool LightTemperature::transferComplete;
uint32_t LightTemperature::transferCount;


void LightTemperature::init(){

	memset(transferData, 0, sizeof(transferData));
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

	powerOn(CHANNEL_LEFT);
	powerOn(CHANNEL_RIGHT);
}

void LightTemperature::stop(void){

	shutDown(CHANNEL_LEFT);
	shutDown(CHANNEL_RIGHT);
	
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

		transferData[actualTransferLength++] = I2C1->RXDR;

	}else if (I2C1->ISR & I2C_ISR_TXIS){

		I2C1->TXDR = transferData[actualTransferLength++];

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






bool LightTemperature::writeBytes(uint8_t channel, uint32_t bytesCount){
	
	I2C1->CR2 = 
		(getSlaveAddress(channel) << (I2C_CR2_SADD_Pos + 1)) + 
		(0 << I2C_CR2_RD_WRN_Pos) + 
		(bytesCount << I2C_CR2_NBYTES_Pos) + 
		0;

	actualTransferLength = 0;

	transferComplete = false;

	I2C1->CR2 |= I2C_CR2_START;

	while(transferComplete == false);
	
	return (actualTransferLength == bytesCount);
}

bool LightTemperature::readBytes(uint8_t channel, uint32_t bytesCount){

	I2C1->CR2 = 
		(getSlaveAddress(channel) << (I2C_CR2_SADD_Pos + 1)) + 
		(1 << I2C_CR2_RD_WRN_Pos) + 
		(bytesCount << I2C_CR2_NBYTES_Pos) + 
		0;

	actualTransferLength = 0;

	transferComplete = false;

	I2C1->CR2 |= I2C_CR2_START;

	while(transferComplete == false);
	
	return (actualTransferLength == bytesCount);
}

bool LightTemperature::setRegisterPointer(uint8_t channel, uint8_t registerPointer){

	transferData[0] = registerPointer;
	return writeBytes(channel, 1);
	
}

bool LightTemperature::getTemp(uint8_t channel){
	
	return (
		(true == setRegisterPointer(channel, LM75A::Register_Temperature)) &&
		(true == readBytes(channel, 2))
		);
}

bool LightTemperature::getTos(uint8_t channel){

	return (
		(true == setRegisterPointer(channel, LM75A::Register_OvertemperatureShutdown)) &&
		(true == readBytes(channel, 2))
		);
}

bool LightTemperature::getThyst(uint8_t channel){

	return (
		(true == setRegisterPointer(channel, LM75A::Register_Hysteresis)) &&
		(true == readBytes(channel, 2))
		);

}

bool LightTemperature::getConf(uint8_t channel){
	
	return (
		(true == setRegisterPointer(channel, LM75A::Register_Configuration)) &&
		(true == readBytes(channel, 1))
		);
	
}

bool LightTemperature::setConf(uint8_t channel, uint8_t confValue){

	transferData[0] = LM75A::Register_Configuration;
	transferData[1] = confValue;
	return writeBytes(channel, 2);
	
	
	
}


int8_t LightTemperature::readTemperature(uint8_t channel){

	if (true == getTemp(channel)){
		return transferData[0];
	}else{
		return ERROR_VALUE;
	}
	
}

void LightTemperature::shutDown(uint8_t channel){
	setConf(channel, LM75A::Configuration_Shutdown);
}
	
void LightTemperature::powerOn(uint8_t channel){
	setConf(channel, LM75A::Configuration_Normal);
}



