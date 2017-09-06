

#include <stdint.h>

#include "UI.h"
#include "Clock.h"
#include "Ports.h"






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

