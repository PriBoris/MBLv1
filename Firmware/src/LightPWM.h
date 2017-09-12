

#ifndef LIGHT_PWM_H
#define LIGHT_PWM_H

#include "Ports.h"

/**
	@ingroup BL
	@{
	@brief Routines for light PWM channels
*/
class LightPWM{
private:
	
	static uint32_t timerPeriod;/**< Timer period in APB1 ticks*/

	/**
	Set ports as PWM outputs contolled by TIMER
	*/
	static void setPortsPWM();

	/**
	Set ports to zero output
	*/
	static void setPortsGPO();


public:

	/**
	Initialize PWM peripheral in low-power mode. Zero duty output.
	*/
	static void init(void);

	/**
	Enable PWM peripheral. Zero duty output.
	*/
	static void start(uint32_t frequencyHz);


	/**
	Disable PWM peripheral. Zero duty output.
	*/
	static void stop(void);
	


};
/**
	@}
*/



#endif //LIGHT_PWM_H
