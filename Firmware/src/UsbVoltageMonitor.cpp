

#include "UsbVoltageMonitor.h"


#include "Ports.h"


#define UUSB_GPIO_PIN	GPIOB, 4


void UsbVoltageMonitor::init(){

/*	SYSCFG->CFGR3 |= SYSCFG_CFGR3_ENBUFLP_VREFINT_COMP; // Enables the buffer used to generate VREFINT references for COMP2. 
	SYSCFG->CFGR3 |= (1 << 0); //  VREFINT voltage enabled in low-power mode (if ULP=1) and scaler for COMP2 enabled
	
	// wait for VREFINT_RDYF

	
	Ports::initAnalogInput(UUSB_GPIO_PIN);	
*/
	
	
}


