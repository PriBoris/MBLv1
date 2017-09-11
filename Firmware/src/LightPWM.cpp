

#include "LightPWM.h"

#include "Clock.h"

/*

PWMCharge PB13 TIM21_CH1 AF6
PWMLeft1 PA15 TIM2_CH1 AF5
PWMLeft2 PB3 TIM2_CH2  AF2
LPWMRight1 PB11 TIM2_CH4 AF2
PWMRight2 PB10 TIM2_CH3 AF2
*/

uint32_t LightPWM::timerPeriod;

void LightPWM::init(uint32_t frequencyHz){

	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // APB1 = 16MHz
	/*
OC1M: Output compare 1 mode
110: PWM mode 1
 In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 
else inactive.
	*/

	timerPeriod = Clock::getFrequencyHzAPB1() / frequencyHz;
	TIM2->ARR = timerPeriod;

	Ports::initAlternate(
		GPIOA,  
		15,
		Ports::GPIO_AF5,
		Ports::GPIO_PushPull,
		Ports::GPIO_FastSpeed,
		Ports::GPIO_NoPull
		);	

	Ports::initAlternate(
		GPIOB,  
		3,
		Ports::GPIO_AF2,
		Ports::GPIO_PushPull,
		Ports::GPIO_FastSpeed,
		Ports::GPIO_NoPull
		);

	Ports::initAlternate(
		GPIOB,  
		11,
		Ports::GPIO_AF2,
		Ports::GPIO_PushPull,
		Ports::GPIO_FastSpeed,
		Ports::GPIO_NoPull
		);

	Ports::initAlternate(
		GPIOB,  
		10,
		Ports::GPIO_AF2,
		Ports::GPIO_PushPull,
		Ports::GPIO_FastSpeed,
		Ports::GPIO_NoPull
		);


}
