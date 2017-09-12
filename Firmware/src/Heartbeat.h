#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <stdint.h>

/**
@ingroup STM32L0xx
@{
@brief Routines for SysTick timer of STM32L0xx

When enabled, the timer counts down from the reload value to zero,
reloads (wraps to) the value in the SYST_RVR on the next clock cycle,
then decrements on subsequent clock cycles.
Writing a value of zero to the SYST_RVR disables the counter on the next wrap. 
When the processor is halted for debugging the counter does not decrement.


*/


class Heartbeat{
private:

	static bool tickFlag;

public:

	/**
	Starts heartbeat timer and its interrupts
	*/
	static void start(uint32_t frequencyHz, uint32_t processorClockHz);

	/**
	Stops heartbeat timer and its interrupts
	*/
	static void stop(void);

	/**
	Returns true if heartbeat ticked
	*/
	static bool ticked(void);

	/**
	Interrupt service routine
	*/
	static void isr(void);


};
/**
	@}
*/


#endif //HEARTBEAT_H
