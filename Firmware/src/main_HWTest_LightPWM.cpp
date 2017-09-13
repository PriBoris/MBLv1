

#include <stdint.h>

#include "Clock.h"
#include "Heartbeat.h"

#include "UI.h"
#include "Ports.h"
#include "LightPWM.h"






int main(){

	Clock::init();
	
	Heartbeat::start(10, Clock::getFrequencyHzSystem());
	
	Ports::init();
	UI::init();
	LightPWM::init();
	
	LightPWM::start(10000, Clock::getFrequencyHzAPB1());
	LightPWM::setChannelDuty(LightPWM::CHANNEL_LEFT_1, 10);	
	LightPWM::setChannelDuty(LightPWM::CHANNEL_LEFT_2, 20);	
	LightPWM::setChannelDuty(LightPWM::CHANNEL_RIGHT_1, 30);	
	LightPWM::setChannelDuty(LightPWM::CHANNEL_RIGHT_2, 40);	
	
	while(true){ 

		if (Heartbeat::ticked()){

			static bool pwmEnabled = false;
			
			if (UI::btnPlusIsPushed()){

				if (pwmEnabled == false){
					UI::ledRed();

					LightPWM::start(10000, Clock::getFrequencyHzAPB1());
					LightPWM::setChannelDuty(LightPWM::CHANNEL_LEFT_1, 10);	
					LightPWM::setChannelDuty(LightPWM::CHANNEL_LEFT_2, 20);	
					LightPWM::setChannelDuty(LightPWM::CHANNEL_RIGHT_1, 30);	
					LightPWM::setChannelDuty(LightPWM::CHANNEL_RIGHT_2, 40);	

					pwmEnabled = true;
				}


			}else{
				
				if (pwmEnabled == true){

					UI::ledOff();

					LightPWM::stop();

					pwmEnabled = false;
				}

			}
			
		}
		

		
	};
	
}

