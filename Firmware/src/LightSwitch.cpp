
#include "LightSwitch.h"

#define LIGHT_SWITCH_GPIO_PIN	GPIOB, 2

void LightSwitch::init(void){

	Ports::initOutput(
		LIGHT_SWITCH_GPIO_PIN,
		Ports::GPIO_OpenDrain,
		Ports::GPIO_LowSpeed,
		Ports::GPIO_Set
		);

	setOff();
}

void LightSwitch::setOn(void){

	Ports::outputReset(LIGHT_SWITCH_GPIO_PIN);
}

void LightSwitch::setOff(void){

	Ports::outputSet(LIGHT_SWITCH_GPIO_PIN);
}



