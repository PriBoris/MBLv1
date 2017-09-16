
#ifndef LIGHT_TEMPERATURE_H
#define LIGHT_TEMPERATURE_H

#include <stdint.h>


/**
	@ingroup BL
	@{
	@brief Routines for measuring LEDs' temperature
*/

class LightTemperature{
private:

	/**
	Set ports as I2C
	*/
	static void setPortsI2C();

	/**
	Set ports to hiZ
	*/
	static void setPortsGPI();



	class LM75A{

/*B1 B0 Selected register
0 0 Temperature register (Temp)
0 1 Conﬁguration register (Conf)
1 0 Hysteresis register (Thyst)
1 1 Overtemperature shutdown register (Tos)
*/	};




public:


	/**
	Initialize in low-power mode
	*/
	static void init();

	/**
	Enable I2C peripheral.
	*/
	static void start(uint32_t apbClockHz);


	/**
	Disable I2C peripheral.
	*/
	static void stop(void);

};
/**
	@}
*/


#endif //LIGHT_TEMPERATURE_H
