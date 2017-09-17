

#include <stdint.h>

#include "Clock.h"
#include "Heartbeat.h"

#include "UI.h"
#include "Ports.h"
#include "LightTemperature.h"

int8_t LightTemperatureLeft = LightTemperature::ERROR_VALUE;
int8_t LightTemperatureRight = LightTemperature::ERROR_VALUE;


int main(){

	Clock::init();
	Heartbeat::init();
	
	Heartbeat::start(10, Clock::getFrequencyHzSystem());
	
	Ports::init();
	UI::init();
	LightTemperature::init();
	
	while(true){

		if (Heartbeat::ticked()){

			static bool active = false;
			
			if (UI::btnCtrlIsPushed() == true){
			
				if (active == false){

					LightTemperature::start(Clock::getFrequencyHzAPB1());

					active = true;
				}
				
				LightTemperatureLeft = LightTemperature::readTemperature(LightTemperature::CHANNEL_LEFT);
				LightTemperatureRight = LightTemperature::readTemperature(LightTemperature::CHANNEL_RIGHT);
			
				static uint8_t toggle = 0;
				if (toggle == 0){
					UI::ledGreen();
				}else{
					UI::ledOff();
				}
				toggle ^= 1;

				
				
			}else{
				
				if (active == true){
				
					LightTemperature::stop();
					active = false;
				}
				
				UI::ledOff();
				
			}
			
			
			
			
		}


	}


}

