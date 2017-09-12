

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
	
	static uint32_t timerPeriodTicks;/**< Timer period in APB1 ticks*/

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
	static void start(uint32_t frequencyHz, uint32_t apbClockHz);


	/**
	Disable PWM peripheral. Zero duty output.
	*/
	static void stop(void);


	static const uint8_t CHANNEL_LEFT_1 = 1;
	static const uint8_t CHANNEL_LEFT_2 = 2;
	static const uint8_t CHANNEL_RIGHT_1 = 4;
	static const uint8_t CHANNEL_RIGHT_2 = 3;

	/**
	Set duty for one of the 4 channels
	*/
	static void setChannelDuty(uint8_t timerChannel, uint32_t dutyPercent);


};
/**
	@}
*/



#endif //LIGHT_PWM_H
