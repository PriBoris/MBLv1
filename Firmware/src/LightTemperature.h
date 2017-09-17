
#ifndef LIGHT_TEMPERATURE_H
#define LIGHT_TEMPERATURE_H

#include <stdint.h>


/**
	@ingroup BL
	@{
	@brief Routines for measuring LEDs' temperature
*/

class LightTemperature{

public:

	static const uint8_t CHANNEL_LEFT = 0;
	static const uint8_t CHANNEL_RIGHT = 1;
	
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
	
		static const uint8_t Configuration_Shutdown = 1;
		static const uint8_t Configuration_Normal = 0;
			
	};

	static const uint32_t TRANSFER_DATA_BUFFER_LENGTH = 32;
	static uint8_t transferData[TRANSFER_DATA_BUFFER_LENGTH];
	static uint32_t actualTransferLength;
	static bool transferComplete;
	static uint32_t transferCount;

	static uint8_t getSlaveAddress(uint8_t channel);

	
	static bool writeBytes(uint8_t channel, uint32_t bytesCount);
	static bool readBytes(uint8_t channel, uint32_t bytesCount);

	static bool setRegisterPointer(uint8_t channel, uint8_t registerPointer);
	static bool getTemp(uint8_t channel);
	static bool getTos(uint8_t channel);
	static bool getThyst(uint8_t channel);

	static bool getConf(uint8_t channel);
	static bool setConf(uint8_t channel, uint8_t confValue);

	static void shutDown(uint8_t channel);
	static void powerOn(uint8_t channel);


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


	/**
	I2C peripheral interrupt service routine
	*/
	static void isr(void);


	static const int8_t ERROR_VALUE = (int8_t)127;


	static int8_t readTemperature(uint8_t channel);

	
	
	
};
/**
	@}
*/


#endif //LIGHT_TEMPERATURE_H
