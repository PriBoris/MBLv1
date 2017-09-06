
#ifndef PORTS_H
#define PORTS_H

#include "stm32l0xx.h"


class Ports{
private:
	enum GpioMode{
		GPIO_Mode_IN,//Input mode 
		GPIO_Mode_OUT,// General purpose output mode
		GPIO_Mode_AF,// Alternate function mode
		GPIO_Mode_AN// Analog mode
	};	


public:
	static void init();

	enum GpioOutputType{
		GPIO_PushPull,// Output push-pull 
		GPIO_OpenDrain  //Output open-drain
	};
	enum GpioPull{
		GPIO_NoPull,
		GPIO_PullUp,
		GPIO_PullDown 
	};
	enum GpioSpeed{
		GPIO_LowSpeed,//fall/rise time 100ns
		GPIO_MediumSpeed,//10ns
		GPIO_FastSpeed,//6ns
		GPIO_HighSpeed//4ns
	};
	enum GpioAF{
		GPIO_AF1_USART1 = 1,
	};
	enum GpioValue{
		Reset = 0,
		Set = 1
	};

	static void initOutput(
		GPIO_TypeDef *  GPIOx,  
		uint32_t pin,
		GpioOutputType gpioOutputType,
		GpioSpeed gpioSpeed,
		GpioValue initValue
		);

	static void initAnalogInput(
		GPIO_TypeDef *  GPIOx,  
		uint32_t pin
		);	

	static void initInput(
		GPIO_TypeDef *  GPIOx,  
		uint32_t pin,
		GpioPull pull
		);	

	static void initAlternate(
		GPIO_TypeDef *  GPIOx,  
		uint32_t pin,
		GpioAF af,
		GpioOutputType gpioOutputType,
		GpioSpeed gpioSpeed,
		GpioPull pull
		);	
	
	static void outputSet(GPIO_TypeDef *GPIOx,uint32_t pin);
	static void outputReset(GPIO_TypeDef *GPIOx,uint32_t pin);
	static bool inputIsSet(GPIO_TypeDef *GPIOx,uint32_t pin);
	static bool inputIsReset(GPIO_TypeDef *GPIOx,uint32_t pin);	

};


#endif //PORTS_H


