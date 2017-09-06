

#include <stdint.h>

#include "UI.h"
#include "Clock.h"
#include "Ports.h"


/**	@mainpage

	@section intro_sec Introduction

	This is the firmware project for the Mirror Backlight V1

	@section intro_tools Tools

	- Keil 5.17
	- ST-Link Debugger
	- Doxygen 1.8.13
	- Python 3.6

*/




int main(){

	Clock::init();
	Ports::init();
	UI::init();
	UI::ledGreen();
	
	while(true){ 

		if (UI::btnPlusIsPushed()){
			UI::ledRed();
		}else if (UI::btnMinusIsPushed()){
			UI::ledGreen();
		}else if (UI::btnCtrlIsPushed()){
			UI::ledYellow();
		}else{
			UI::ledOff();
		}

		__asm("  nop");
		
	};
	
}

