

#include <stdint.h>

#include "UI.h"
#include "Clock.h"





int main(){

	Clock::init();
	UI::init();
	
	uint32_t i = 0;
	while(true){ 
		i++;
		__asm("  nop");
		
	};
	
}

