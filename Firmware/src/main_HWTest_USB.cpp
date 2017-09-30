


#include <stdint.h>

#include "Clock.h"
#include "Heartbeat.h"
#include "Analog.h"


#include "UI.h"
#include "Ports.h"
#include "UsbVoltageMonitor.h"


class AdcResults{
public:
	uint32_t vcc;
	uint32_t vbat;
	int32_t temperature;
		
	
	
};

AdcResults adcResults;

int main(){

	Clock::init();
	Heartbeat::init();
	
	Heartbeat::start(10, Clock::getFrequencyHzSystem());
	
	Ports::init();
	Analog::init();
	UI::init();
	
	Analog::start();
	
	//Analog::stop();
	
	while(true){ 

		if (Heartbeat::ticked()){

			if (Analog::getComparatorOutput() == true){
				
				UI::ledRed();
			}else{
					
				UI::ledGreen();
			}
			
			if (Analog::adcSequenceIsComplete()){
				
				adcResults.vcc = Analog::getVccMillivolts();
				adcResults.vbat = Analog::getVbatMillivolts();
				adcResults.temperature = Analog::getTemperatureDegrees();
			}
		}
		
	};
	
}


