


#include <stdint.h>

#include "Clock.h"
#include "Heartbeat.h"

#include "UI.h"
#include "Ports.h"
#include "UsbVoltageMonitor.h"






int main(){

	Clock::init();
	Heartbeat::init();
	
	Heartbeat::start(10, Clock::getFrequencyHzSystem());
	
	Ports::init();
	UI::init();
	
	UsbVoltageMonitor::init();
	
	while(true){ 

		if (Heartbeat::ticked()){

			
		}
		
	};
	
}


