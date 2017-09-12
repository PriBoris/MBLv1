

#include "Heartbeat.h"

#include "stm32l0xx.h"

bool Heartbeat::tickFlag;

void Heartbeat::start(uint32_t frequencyHz, uint32_t processorClockHz){

/*
If the SysTick counter reload and current value are undefined at reset, the correct 
initialization sequence for the SysTick counter is: 
1. Program reload value.
2.  Clear current value.
3.  Program Control and Status register.
*/	
	tickFlag = false;
	SysTick->LOAD = processorClockHz / frequencyHz;
	SysTick->VAL = 0;
	SysTick->CTRL = 
		SysTick_CTRL_ENABLE_Msk + //1 = Counter enabled.
		SysTick_CTRL_TICKINT_Msk + //1 = Counting down to zero to asserts the SysTick exception request.
		SysTick_CTRL_CLKSOURCE_Msk + //1 = Processor clock is SysTick timer clock source
		0;

}

void Heartbeat::stop(){

	SysTick->LOAD = 0;
	SysTick->CTRL = 0;
	tickFlag = false;
}

bool Heartbeat::ticked(void){
	
	if (tickFlag == true){
		tickFlag = false; 
		return true;
	}else{
		return false;
	}
}

void Heartbeat::isr(void){
		
	tickFlag = true;
}

extern "C"{ void SysTick_Handler(){
	Heartbeat::isr();
}}
