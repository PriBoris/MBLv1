

#include "Clock.h"


#include "stm32l0xx.h"

void Clock::init(){

	//enable 16MHz internal high-speed oscillator (HSI)
	RCC->CR |= RCC_CR_HSION;
	while(true){
		if (RCC->CR & RCC_CR_HSIRDY){
			break;
		}
	}

	//use HSI16 as system clock
	RCC->CFGR &= RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while(true){
		if ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_HSI){
			break;
		}
		
	}
	
}


