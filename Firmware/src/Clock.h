
#ifndef CLOCK_H
#define CLOCK_H

/**
	@defgroup STM32L0xx STM32L0xx microcontroller
	@brief Hardware dependent routines
*/

#include <stdint.h>

/**
	@ingroup STM32L0xx
	@{
	@brief Routines for initializing Clocks of STM32L0xx
*/
class Clock{
private:
	static const uint32_t HSI_FREQUENCY_HZ = 16000000;
public:
	static void init();

	static uint32_t getFrequencyHzAPB1();

	static uint32_t getFrequencyHzSystem();


};


/**
	@}
*/


#endif //CLOCK_H
