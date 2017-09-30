
#ifndef ANALOG_H
#define ANALOG_H

#include <stdint.h>

class Analog{
private:

	static const uint32_t VREFINT_CAL = 0x1FF80078;
	static const uint32_t TSENSE_CAL1 = 0x1FF8007A;
	static const uint32_t TSENSE_CAL2 = 0x1FF8007E;

	static uint16_t vrefintCalValue;
	static uint16_t tsenseCal1Value;
	static uint16_t tsenseCal2Value;	
	static int16_t tsense1Value;
	static int16_t tsense2Value;	

	static void adcEnable();
	static void adcStart();

	static uint32_t ovrCounter;

	static const uint_fast8_t ADC_CHANNEL_COUNT = 12;
	static uint32_t adcData[ADC_CHANNEL_COUNT];
	static uint_fast8_t actualAdcChannel;
	static uint32_t vccMillivolts;

	static const uint_fast8_t ADC_CHANNEL_Uleft1 = 0;
	static const uint_fast8_t ADC_CHANNEL_Uleft2 = 1;
	static const uint_fast8_t ADC_CHANNEL_Ileft1 = 2;
	static const uint_fast8_t ADC_CHANNEL_Ileft2 = 3;
	static const uint_fast8_t ADC_CHANNEL_Iright2 = 4;
	static const uint_fast8_t ADC_CHANNEL_Iright1 = 5;
	static const uint_fast8_t ADC_CHANNEL_Uright2 = 6;
	static const uint_fast8_t ADC_CHANNEL_Uright1 = 7;
	static const uint_fast8_t ADC_CHANNEL_Icharge = 8;
	static const uint_fast8_t ADC_CHANNEL_UBat = 9;
	static const uint_fast8_t ADC_CHANNEL_VRefInt = 10;
	static const uint_fast8_t ADC_CHANNEL_TSensor = 11;


	static const uint32_t ADC_GAIN_NOM_Ubat = 2;
	static const uint32_t ADC_GAIN_DENOM_Ubat = 1;

/*
Uleft1 PA0  ADC_IN0
Uleft2 PA1 ADC_IN1
Ileft1 PA2  ADC_IN2
Ileft2 PA3 ADC_IN3
Iright2 PA4 ADC_IN4
Iright1 PA5 ADC_IN5
Uright2 PA6 ADC_IN6
Uright1 PA7 ADC_IN7
Icharge PB0 ADC_IN8
UBat PB1 ADC_IN9
VRefInt ADC_IN17
TSensor ADC_IN18
*/


	static bool endOfSequenceFlag;

	static const uint32_t VREFINT_VOLTAGE_MILLIVOLTS = 1224;
	static const uint32_t ADC_MAX_CODE = 4096;

public:
	static void init();

	static void start();

	static void stop();

	static bool getComparatorOutput();

	static void isr();

	static bool adcSequenceIsComplete();

	static uint32_t getVccMillivolts();
	static uint32_t getVbatMillivolts();
	static int32_t getTemperatureDegrees();

};




#endif //ANALOG_H
