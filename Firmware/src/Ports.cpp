
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
//=================================================================================================
void Ports::initOutput(
	GPIO_TypeDef *  GPIOx,  
	uint32_t pin,
	GpioOutputType gpioOutputType,
	GpioSpeed gpioSpeed,
	GpioValue initValue
	){
		
	GPIOx->MODER &= ~((uint32_t)(3<<(2*pin)));
	GPIOx->MODER |= ((uint32_t)(1<<(2*pin)));
		
		
	switch(gpioOutputType){
	case GPIO_PushPull:
		GPIOx->OTYPER &= ~((uint32_t)(1<<pin));
		break;
	case GPIO_OpenDrain:
		GPIOx->OTYPER |= ((uint32_t)(1<<pin));
		GPIOx->PUPDR &= ~((uint32_t)(3<<(2*pin))); //GPIO_NoPull



		break;
	}

	GPIOx->OSPEEDR &= ~((uint32_t)(3<<(2*pin)));		
	switch(gpioSpeed){
	case GPIO_LowSpeed:
		break;
	case GPIO_MediumSpeed:
		GPIOx->OSPEEDR |= ((uint32_t)(1<<(2*pin)));
		break;
	case GPIO_FastSpeed:
		GPIOx->OSPEEDR |= ((uint32_t)(2<<(2*pin)));
		break;
	case GPIO_HighSpeed:
		GPIOx->OSPEEDR |= ((uint32_t)(3<<(2*pin)));
		break;
	}

	if (initValue==GPIO_Reset){
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
void Ports::initInput(
	GPIO_TypeDef *  GPIOx,  
	uint32_t pin,
	GpioPull pull
	){

	GPIOx->MODER &= ~((uint32_t)(3<<(2*pin)));
		

	GPIOx->PUPDR &= ~((uint32_t)(3<<(2*pin)));
	switch(pull){
	case GPIO_NoPull:
		break;
	case GPIO_PullUp:
		GPIOx->PUPDR |= ((uint32_t)(1<<(2*pin)));
		break;
	case GPIO_PullDown: 
		GPIOx->PUPDR |= ((uint32_t)(2<<(2*pin)));
		break;
	}
		
}
//=================================================================================================
bool Ports::inputIsSet(GPIO_TypeDef *GPIOx,uint32_t pin){
	return ((GPIOx->IDR&(1<<pin))!=0);
}
bool Ports::inputIsReset(GPIO_TypeDef *GPIOx,uint32_t pin){
	return ((GPIOx->IDR&(1<<pin))==0);
}
//=================================================================================================
void Ports::initAlternate(
	GPIO_TypeDef *GPIOx,  
	uint32_t pin,
	GpioAF af,
	GpioOutputType gpioOutputType,
	GpioSpeed gpioSpeed,
	GpioPull pull
	){

	GPIOx->MODER &= ~((uint32_t)(3<<(2*pin)));
	GPIOx->MODER |= ((uint32_t)(2<<(2*pin)));

	switch(gpioOutputType){
	case GPIO_PushPull	:
		GPIOx->OTYPER &= ~((uint32_t)(1<<pin));
		break;
	case GPIO_OpenDrain:
		GPIOx->OTYPER |= ((uint32_t)(1<<pin));
		break;
	}

	GPIOx->OSPEEDR &= ~((uint32_t)(3<<(2*pin)));		
	switch(gpioSpeed){
	case GPIO_LowSpeed:
		break;
	case GPIO_MediumSpeed:
		GPIOx->OSPEEDR |= ((uint32_t)(1<<(2*pin)));
		break;
	case GPIO_FastSpeed:
		GPIOx->OSPEEDR |= ((uint32_t)(2<<(2*pin)));
		break;
	case GPIO_HighSpeed:
		GPIOx->OSPEEDR |= ((uint32_t)(3<<(2*pin)));
		break;
	}

	GPIOx->PUPDR &= ~((uint32_t)(3<<(2*pin)));
	switch(pull){
	case GPIO_NoPull:
		break;
	case GPIO_PullUp:
		GPIOx->PUPDR |= ((uint32_t)(1<<(2*pin)));
		break;
	case GPIO_PullDown: 
		GPIOx->PUPDR |= ((uint32_t)(2<<(2*pin)));
		break;
	}

	if(pin<8){
		GPIOx->AFR[0] &= ~((uint32_t)(15<<(4*pin)));
		GPIOx->AFR[0] |= ((uint32_t)((af)<<(4*pin)));
	}else{
		GPIOx->AFR[1] &= ~((uint32_t)(15<<(4*(pin-8))));
		GPIOx->AFR[1] |= ((uint32_t)((af)<<(4*(pin-8))));
	}





}
//=================================================================================================
