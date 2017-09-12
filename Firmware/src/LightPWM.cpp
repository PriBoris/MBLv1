

#include "LightPWM.h"



#define LIGHT_PWM_LEFT1_PIN		GPIOA, 15
#define LIGHT_PWM_LEFT2_PIN		GPIOB, 3
#define LIGHT_PWM_RIGHT1_PIN	GPIOB, 11
#define LIGHT_PWM_RIGHT2_PIN	GPIOB, 10

#define LIGHT_PWM_LEFT1_AF		Ports::GPIO_AF5
#define LIGHT_PWM_LEFT2_AF		Ports::GPIO_AF2
#define LIGHT_PWM_RIGHT1_AF		Ports::GPIO_AF2
#define LIGHT_PWM_RIGHT2_AF		Ports::GPIO_AF2




uint32_t LightPWM::timerPeriodTicks;



void LightPWM::init(void){

	setPortsGPO();


}


void LightPWM::start(uint32_t frequencyHz, uint32_t apbClockHz){
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 

	
	TIM2->PSC = 0; // prescaler = 1
	timerPeriodTicks = apbClockHz / frequencyHz;
	TIM2->ARR = timerPeriodTicks;
	TIM2->CCER = 
		TIM_CCER_CC1E + TIM_CCER_CC2E + TIM_CCER_CC3E + TIM_CCER_CC4E + // enable outputs
		0*(TIM_CCER_CC1P + TIM_CCER_CC2P + TIM_CCER_CC3P + TIM_CCER_CC4P) + // active high
		0;
	
	/*
	OC1M:
	100: Force inactive level
	110: PWM mode 1
	*/
	TIM2->CCMR1 = 
		TIM_CCMR1_OC1PE + // Output compare 1 preload enable
		TIM_CCMR1_OC2PE + // Output compare 2 preload enable
		TIM_CCMR1_OC1M_2 + //
		TIM_CCMR1_OC2M_2 + //
		0;
	TIM2->CCMR2 = 
		TIM_CCMR2_OC3PE + // Output compare 3 preload enable
		TIM_CCMR2_OC4PE + // Output compare 4 preload enable
		TIM_CCMR2_OC3M_2 + //
		TIM_CCMR2_OC4M_2 + //
		0;
	
	setChannelDuty(CHANNEL_LEFT_1, 0);
	setChannelDuty(CHANNEL_LEFT_2, 0);
	setChannelDuty(CHANNEL_RIGHT_1, 0);
	setChannelDuty(CHANNEL_RIGHT_2, 0);

	TIM2->CR1 = 
		0 * TIM_CR1_ARPE + //0: TIMx_ARR register is not buffered
		0 * TIM_CR1_DIR + //0: Counter used as upcounter
		0 * TIM_CR1_OPM + //0: Counter is not stopped at update event
		TIM_CR1_CEN + //1: Counter enabled
		0;

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

void LightPWM::setChannelDuty(uint8_t timerChannel, uint32_t dutyPercent){

	uint32_t dutyTicks = dutyPercent;
	dutyTicks *= timerPeriodTicks;
	dutyTicks /= 100;

	if (dutyTicks <=0 ){

		switch(timerChannel){
		case 1:
			TIM2->CCMR1 &= ~(TIM_CCMR1_OC1M_1);	
			break;
		case 2:
			TIM2->CCMR1 &= ~(TIM_CCMR1_OC2M_1);	
			break;
		case 3:
			TIM2->CCMR2 &= ~(TIM_CCMR2_OC3M_1);	
			break;
		case 4:
			TIM2->CCMR2 &= ~(TIM_CCMR2_OC4M_1);	
			break;
		}


	}else{


		switch(timerChannel){
		case 1:
			TIM2->CCR1 = dutyTicks;
			TIM2->CCMR1 |= TIM_CCMR1_OC1M_1;	
			break;
		case 2:
			TIM2->CCR2 = dutyTicks;
			TIM2->CCMR1 |= TIM_CCMR1_OC2M_1;	
			break;
		case 3:
			TIM2->CCR3 = dutyTicks;
			TIM2->CCMR2 |= TIM_CCMR2_OC3M_1;	
			break;
		case 4:
			TIM2->CCR4 = dutyTicks;
			TIM2->CCMR2 |= TIM_CCMR2_OC4M_1;	
			break;
		}


	}


	
}

