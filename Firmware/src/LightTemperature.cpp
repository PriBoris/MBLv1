
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

	__asm("	nop");
	
	if (I2C1->ISR & I2C_ISR_NACKF){
		I2C1->ICR = I2C_ICR_NACKCF;
	}else if (I2C1->ISR & I2C_ISR_STOPF){
		I2C1->ICR = I2C_ICR_STOPCF;
	}else if (I2C1->ISR & I2C_ISR_RXNE){
		I2C1->ICR = I2C_ICR_STOPCF;
	}else{
		__asm("	nop");
	}

/*	
#define I2C_ISR_TXE                  I2C_ISR_TXE_Msk                      //Transmit data register empty 
#define I2C_ISR_RXNE                 I2C_ISR_RXNE_Msk                     //Receive data register not empty 
#define I2C_ISR_NACKF                I2C_ISR_NACKF_Msk                    //NACK received flag 
#define I2C_ISR_STOPF                I2C_ISR_STOPF_Msk                    //STOP detection flag 
#define I2C_ISR_TC                   I2C_ISR_TC_Msk                       //Transfer complete (master mode) 
#define I2C_ISR_TCR                  I2C_ISR_TCR_Msk                      //Transfer complete reload 
#define I2C_ISR_BERR                 I2C_ISR_BERR_Msk                     //Bus error 
#define I2C_ISR_ARLO                 I2C_ISR_ARLO_Msk                     //Arbitration lost 
#define I2C_ISR_OVR                  I2C_ISR_OVR_Msk                      //Overrun/Underrun 
#define I2C_ISR_PECERR               I2C_ISR_PECERR_Msk                   //PEC error in reception 
#define I2C_ISR_TIMEOUT              I2C_ISR_TIMEOUT_Msk                  //Timeout or Tlow detection flag 
#define I2C_ISR_ALERT                I2C_ISR_ALERT_Msk                    //SMBus alert 
#define I2C_ISR_BUSY                 I2C_ISR_BUSY_Msk                     //Bus busy 
#define I2C_ISR_DIR                  I2C_ISR_DIR_Msk                      //Transfer direction (slave mode) 
#define I2C_ISR_ADDCODE              I2C_ISR_ADDCODE_Msk                  //Address match code (slave mode) 
*/	
	
}}


void LightTemperature::readSmth(){

/*
Addressing mode (7-bit or 10-bit): ADD10 
• Slave address to be sent: SADD[9:0] 
• Transfer direction: RD_WRN
The number of bytes to be transferred: NBYTES[7:0]. If the number of bytes is equal to 
or greater than 255 bytes, NBYTES[7:0] must initially be filled with 0xFF.

The user must then set the START bit in I2C_CR2 register. Changing all the above bits is 
not allowed when START bit is set.
*/	

	I2C1->CR2 = 
		((LM75A::AddressBase + 1) << (I2C_CR2_SADD_Pos+1)) + 
		(1 << I2C_CR2_RD_WRN_Pos) + // Master requests a read transfer.
		(2 << I2C_CR2_NBYTES_Pos) + // Number of bytes
		0;

	I2C1->CR2 |= I2C_CR2_START;
	



	
}



