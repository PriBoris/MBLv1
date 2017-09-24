
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

public:
	static void init();

	static void start();

	static void stop();

};




#endif //ANALOG_H
