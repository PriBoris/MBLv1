
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
	public:
		static const uint8_t Register_Temperature = 0;
		static const uint8_t Register_Configuration = 1;
		static const uint8_t Register_Hysteresis = 2;
		static const uint8_t Register_OvertemperatureShutdown = 3;
	
		static const uint8_t AddressBase = 0x48;
	};




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


	static void readSmth();


};
/**
	@}
*/


#endif //LIGHT_TEMPERATURE_H
