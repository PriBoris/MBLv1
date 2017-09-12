

#include <stdint.h>

#include "Clock.h"
#include "Heartbeat.h"

#include "UI.h"
#include "Ports.h"
#include "LightPWM.h"






int main(){

	Clock::init();
	Heartbeat::start(2);
	
	Ports::init();
	UI::init();
	LightPWM::init();
	
	UI::ledOff();
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
