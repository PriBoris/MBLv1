

#include "LightPWM.h"

#include "Clock.h"

/*

PWMCharge PB13 TIM21_CH1 AF6
PWMLeft1 PA15 TIM2_CH1 AF5
PWMLeft2 PB3 TIM2_CH2  AF2
LPWMRight1 PB11 TIM2_CH4 AF2
PWMRight2 PB10 TIM2_CH3 AF2

*/

#define LIGHT_PWM_LEFT1_PIN		GPIOA, 15
#define LIGHT_PWM_LEFT2_PIN		GPIOB, 3
#define LIGHT_PWM_RIGHT1_PIN	GPIOB, 11
#define LIGHT_PWM_RIGHT2_PIN	GPIOB, 10

#define LIGHT_PWM_LEFT1_AF		Ports::GPIO_AF5
#define LIGHT_PWM_LEFT2_AF		Ports::GPIO_AF2
#define LIGHT_PWM_RIGHT1_AF		Ports::GPIO_AF2
#define LIGHT_PWM_RIGHT2_AF		Ports::GPIO_AF2



uint32_t LightPWM::timerPeriod;



void LightPWM::init(void){

	setPortsGPO();


}


void LightPWM::start(uint32_t frequencyHz){
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 


	// APB1 = 16MHz
	/*
OC1M: Output compare 1 mode
110: PWM mode 1
 In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 
else inactive.
	*/

//	timerPeriod = Clock::getFrequencyHzAPB1() / frequencyHz;
//	TIM2->ARR = timerPeriod;

	setPortsPWM();
	
}

void LightPWM::stop(){

	setPortsGPO();
	RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN);
	
}

void LightPWM::setPortsPWM(){

	Ports::initAlternate(
		LIGHT_PWM_LEFT1_PIN,
		LIGHT_PWM_LEFT1_AF,
		Ports::GPIO_PushPull,
		Ports::GPIO_FastSpeed,
		Ports::GPIO_NoPull
		);	

	Ports::initAlternate(
		LIGHT_PWM_LEFT2_PIN,
		LIGHT_PWM_LEFT2_AF,
		Ports::GPIO_PushPull,
		Ports::GPIO_FastSpeed,
		Ports::GPIO_NoPull
		);

	Ports::initAlternate(
		LIGHT_PWM_RIGHT1_PIN,
		LIGHT_PWM_RIGHT1_AF,
		Ports::GPIO_PushPull,
		Ports::GPIO_FastSpeed,
		Ports::GPIO_NoPull
		);

	Ports::initAlternate(
		LIGHT_PWM_RIGHT2_PIN,
		LIGHT_PWM_RIGHT2_AF,
		Ports::GPIO_PushPull,
		Ports::GPIO_FastSpeed,
		Ports::GPIO_NoPull
		);
	
}

void LightPWM::setPortsGPO(){
	
	Ports::initOutput(
		LIGHT_PWM_LEFT1_PIN,
		Ports::GPIO_PushPull,
		Ports::GPIO_LowSpeed,
		Ports::GPIO_Reset
		);	

	Ports::initOutput(
		LIGHT_PWM_LEFT2_PIN,
		Ports::GPIO_PushPull,
		Ports::GPIO_LowSpeed,
		Ports::GPIO_Reset
		);

	Ports::initOutput(
		LIGHT_PWM_RIGHT1_PIN,
		Ports::GPIO_PushPull,
		Ports::GPIO_LowSpeed,
		Ports::GPIO_Reset
		);

	Ports::initOutput(
		LIGHT_PWM_RIGHT2_PIN,
		Ports::GPIO_PushPull,
		Ports::GPIO_LowSpeed,
		Ports::GPIO_Reset
		);
}


