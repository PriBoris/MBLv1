

#include <stdint.h>

#include "Clock.h"
#include "Heartbeat.h"

#include "UI.h"
#include "Ports.h"
#include "LightTemperature.h"


int main(){

	Clock::init();
	
	Heartbeat::start(10, Clock::getFrequencyHzSystem());
	
	Ports::init();
	UI::init();
	LightTemperature::init();
	
	LightTemperature::start(Clock::getFrequencyHzAPB1());
	

	while(true){



	}


}

