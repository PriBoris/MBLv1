
#include "Analog.h"

#include "stm32l0xx.h"

uint16_t Analog::vrefintCalValue;
uint16_t Analog::tsenseCal1Value;
uint16_t Analog::tsenseCal2Value;	


void Analog::init(){

	vrefintCalValue = *(uint16_t*)VREFINT_CAL;
	tsenseCal1Value = *(uint16_t*)TSENSE_CAL1;
	tsenseCal2Value = *(uint16_t*)TSENSE_CAL2;
	
	
}

void Analog::start(){

	SYSCFG->CFGR3 |= (
		SYSCFG_CFGR3_ENBUF_VREFINT_ADC | //
		SYSCFG_CFGR3_ENBUF_SENSOR_ADC | //
		SYSCFG_CFGR3_ENBUFLP_VREFINT_COMP | //
		SYSCFG_CFGR3_ENREF_HSI48 //
		);
	
	while(true){
		if (((SYSCFG->CFGR3) & SYSCFG_CFGR3_VREFINT_RDYF) != 0){
			break;
		}
	}

}

void Analog::stop(){

	SYSCFG->CFGR3 &= ~(
		SYSCFG_CFGR3_ENBUF_VREFINT_ADC | //
		SYSCFG_CFGR3_ENBUF_SENSOR_ADC | //
		SYSCFG_CFGR3_ENBUFLP_VREFINT_COMP | //
		SYSCFG_CFGR3_ENREF_HSI48
		);

/*	while(true){
		if (((SYSCFG->CFGR3) & SYSCFG_CFGR3_VREFINT_RDYF) == 0){
			break;
		}
	}*/

	__asm("	nop");

	
	
}






