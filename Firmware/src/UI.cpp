
#include "UI.h"


#include "Ports.h"

/*
PB14 BtnMinus
PB15 BtnPlus
PA8 BtnCtrl
PA9 LedGreen
PA10 LedRed
*/


void UI::init(){

	Ports::initOutput(
		GPIOA,  
		9,
		Ports::GPIO_PushPull,
		Ports::GPIO_LowSpeed,
		Ports::Reset
		);

	Ports::initOutput(
		GPIOA,  
		10,
		Ports::GPIO_PushPull,
		Ports::GPIO_LowSpeed,
		Ports::Reset
		);
	
}

void UI::ledRed(){

	Ports::outputSet(GPIOA, 9);
	Ports::outputReset(GPIOA, 10);

}

void UI::ledGreen(){

	Ports::outputReset(GPIOA, 9);
	Ports::outputSet(GPIOA, 10);

}

void UI::ledYellow(){

	Ports::outputSet(GPIOA, 9);
	Ports::outputSet(GPIOA, 10);

}

void UI::ledOff(){

	Ports::outputReset(GPIOA, 9);
	Ports::outputReset(GPIOA, 10);

}



