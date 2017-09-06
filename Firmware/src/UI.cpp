
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
		Ports::OutputType::PushPull,
		Ports::OutputSpeed::LowSpeed,
		Ports::LowSpeed::Reset
		);


}

