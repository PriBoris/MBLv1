

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
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while(true){
		if ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_HSI){
			break;
		}
	}

	// APB1 = low-speed peripheral bus
	// APB2 = high-speed peripheral bus
	// AHB =  advanced high-performance bus.
	// Prescalers:
	RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
	RCC->CFGR |= (RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV1 | RCC_CFGR_PPRE2_DIV1);

	// System configuration controller clock enabled
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; 


}

uint32_t Clock::getFrequencyHzAPB1(){
	
	return HSI_FREQUENCY_HZ/1;
}

uint32_t Clock::getFrequencyHzSystem(){
	
	return HSI_FREQUENCY_HZ/1;
}


