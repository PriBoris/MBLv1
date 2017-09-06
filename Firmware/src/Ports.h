
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

	
	class OutputType{
		static const uint8_t PushPull = 0;// Output push-pull 
		static const uint8_t OpenDrain = 1;//Output open-drain
	};
	class Pull{
		static const uint8_t NoPull = 0;
		static const uint8_t PullUp = 1;
		static const uint8_t PullDown = 2; 
	};
	class OutputSpeed{
		static const uint8_t LowSpeed = 0;//fall/rise time 100ns
		static const uint8_t MediumSpeed = 1;//10ns
		static const uint8_t FastSpeed = 2;//6ns
		static const uint8_t HighSpeed = 3;//4ns
	};
	class OutputState{
		static const uint8_t Reset = 0;
		static const uint8_t Set = 1;
	};

	static void initOutput(
		GPIO_TypeDef *  GPIOx,  
		uint32_t pin,
		OutputType outputType,
		OutputSpeed outputSpeed,
		OutputState initOutputState
		);

/*	
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
*/	
	static void outputSet(GPIO_TypeDef *GPIOx,uint32_t pin);
	static void outputReset(GPIO_TypeDef *GPIOx,uint32_t pin);
	static bool inputIsSet(GPIO_TypeDef *GPIOx,uint32_t pin);
	static bool inputIsReset(GPIO_TypeDef *GPIOx,uint32_t pin);

};


#endif //PORTS_H


