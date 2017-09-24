


#include <stdint.h>

#include "Clock.h"
#include "Heartbeat.h"
#include "Analog.h"


#include "UI.h"
#include "Ports.h"
#include "UsbVoltageMonitor.h"






int main(){

	Clock::init();
	Heartbeat::init();
	
	Heartbeat::start(10, Clock::getFrequencyHzSystem());
	
	Ports::init();
	Analog::init();
	UI::init();
	
//	UsbVoltageMonitor::init();
	
	Analog::start();
	
	//Analog::stop();
	
	while(true){ 

		if (Heartbeat::ticked()){

			
		}
		
	};
	
}


