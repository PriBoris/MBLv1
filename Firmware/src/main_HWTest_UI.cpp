

#include <stdint.h>

#include "UI.h"
#include "Clock.h"
#include "Heartbeat.h"

#include "Ports.h"






int main(){

	Clock::init();
	Ports::init();
	
	Heartbeat::start(2, Clock::getFrequencyHzSystem());
	
	UI::init();
	UI::ledOff();
	
	while(true){ 

		if (UI::btnPlusIsPushed()){
			
			UI::ledRed();
		}else if (UI::btnMinusIsPushed()){
			
			UI::ledGreen();
		}else if (UI::btnCtrlIsPushed()){
			
			UI::ledYellow();
		}else{
			
		}

		{
			static uint8_t ledTogle = 0;
			if (Heartbeat::ticked()){
				if (ledTogle == 0){
					UI::ledOff();
				}else{
					UI::ledGreen();
				}
				ledTogle ^= 1;
			}
		}
		
		__asm("  nop");
		
	};
	
}

