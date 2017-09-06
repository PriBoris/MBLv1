

#include <stdint.h>

#include "UI.h"
#include "Clock.h"
#include "Ports.h"





int main(){

	Clock::init();
	Ports::init();
	UI::init();
	
	uint32_t i = 0;
	while(true){ 
		i++;
		__asm("  nop");
		
	};
	
}

