
#include "Ports.h"

#include "stm32l0xx.h"

//=================================================================================================
void Ports::init(){


	RCC->IOPENR = 
		RCC_IOPENR_GPIOAEN + 
		RCC_IOPENR_GPIOBEN + 
		RCC_IOPENR_GPIOCEN + 
		RCC_IOPENR_GPIODEN + 
		RCC_IOPENR_GPIOHEN + 
		0;

}
//=================================================================================================
void Ports::initOutput(
	GPIO_TypeDef *  GPIOx,  
	uint32_t pin,
	OutputType outputType,
	OutputSpeed outputSpeed,
	OutputState initOutputState
	){
		
	GPIOx->MODER &= ~((uint32_t)(3<<(2*pin)));
	GPIOx->MODER |= ((uint32_t)(1<<(2*pin)));
		
		
	switch(outputType){
	case PushPull:
		GPIOx->OTYPER &= ~((uint32_t)(1<<pin));
		break;
	case OpenDrain:
		GPIOx->OTYPER |= ((uint32_t)(1<<pin));
		break;
	}

	GPIOx->OSPEEDR &= ~((uint32_t)(3<<(2*pin)));		
	switch(outputSpeed){
	case LowSpeed:
		break;
	case MediumSpeed:
		GPIOx->OSPEEDR |= ((uint32_t)(1<<(2*pin)));
		break;
	case FastSpeed:
		GPIOx->OSPEEDR |= ((uint32_t)(2<<(2*pin)));
		break;
	case HighSpeed:
		GPIOx->OSPEEDR |= ((uint32_t)(3<<(2*pin)));
		break;
	}

	if (initOutputState==Reset){
		outputReset(GPIOx,pin);		
	}else{
		outputSet(GPIOx,pin);		
	}
	
	
}
//=================================================================================================
void Ports::outputSet(GPIO_TypeDef *GPIOx,uint32_t pin){
	GPIOx->BSRR |= (1<<pin);
}
//=================================================================================================
void Ports::outputReset(GPIO_TypeDef *GPIOx,uint32_t pin){
	GPIOx->BSRR |= (1<<(16+pin));
}
//=================================================================================================
