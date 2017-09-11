

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
	static uint32_t timerPeriod;
public:

	static void init(uint32_t frequencyHz);

};
/**
	@}
*/



#endif //LIGHT_PWM_H
