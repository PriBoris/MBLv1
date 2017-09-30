
#include "Analog.h"

#include <string.h>

#include "stm32l0xx.h"

uint16_t Analog::vrefintCalValue;
uint16_t Analog::tsenseCal1Value;
uint16_t Analog::tsenseCal2Value;	
int16_t Analog::tsense1Value;
int16_t Analog::tsense2Value;	

uint32_t Analog::ovrCounter;

uint32_t Analog::adcData[Analog::ADC_CHANNEL_COUNT];
uint_fast8_t Analog::actualAdcChannel;

bool Analog::endOfSequenceFlag;

uint32_t Analog::vccMillivolts;


void Analog::init(){

	vrefintCalValue = *(uint16_t*)VREFINT_CAL;
	tsenseCal1Value = *(uint16_t*)TSENSE_CAL1;
	tsenseCal2Value = *(uint16_t*)TSENSE_CAL2;
	tsense1Value = 30;
	tsense2Value = 130;

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

	COMP2->CSR = 
		(1 << 8) + //  Comparator 2 Input Plus connection  = PB4
		(0 << 4) + //  Comparator 2 Input Minus connection = VREFINT
		(0 << 3) + //  slow speed
		COMP_CSR_COMP2EN + //  Comparator 2 switched ON. 
		0;

	ovrCounter = 0;

	actualAdcChannel = 0;
	memset(adcData, 0, sizeof(adcData));
	endOfSequenceFlag = false;
	
	RCC->APB2ENR |= RCC_APB2ENR_ADCEN;

	ADC->CCR = (1 << 23); //  Temperature sensor enabled
	
	ADC1->CHSELR = 
		ADC_CHSELR_CHSEL0 + // Uleft1
		ADC_CHSELR_CHSEL1 + // Uleft2
		ADC_CHSELR_CHSEL7 + // Uright1
		ADC_CHSELR_CHSEL6 + // Uright2
		ADC_CHSELR_CHSEL2 + // Ileft1
		ADC_CHSELR_CHSEL3 + // Ileft2
		ADC_CHSELR_CHSEL5 + // Iright1
		ADC_CHSELR_CHSEL4 + // Iright2
		ADC_CHSELR_CHSEL9 + // UBat
		ADC_CHSELR_CHSEL8 + // Icharge
		ADC_CHSELR_CHSEL17 + // internal voltage reference
		ADC_CHSELR_CHSEL18 + // Temperature sensor 
		0;
		
	ADC1->SMPR = (3 << 0); //  Sampling time = 160.5 ADC clock cycles
	
	ADC1->CFGR2 = 
		((uint32_t)2 << 30) + // ADC clock mode = PCLK/4 (Synchronous clock mode)
		0;

	ADC1->CFGR1 = 
		ADC_CFGR1_CONT + 
		0;
		
	ADC1->IER = 
		ADC_IER_EOCIE + //  End of conversion interrupt enable
		ADC_IER_OVRIE + // Overrun interrupt enable
		0;

	adcEnable();
	
	NVIC_EnableIRQ(ADC1_COMP_IRQn);
	adcStart();

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

bool Analog::getComparatorOutput(){
	
	return ((COMP2->CSR & COMP_CSR_COMP2VALUE) != 0);
	
}

extern "C"{void ADC1_COMP_IRQHandler(){
	Analog::isr();
}}
void Analog::isr(){
	
	if (ADC1->ISR & ADC_ISR_EOC){
		
		adcData[actualAdcChannel++] = ADC1->DR;
		if (actualAdcChannel == ADC_CHANNEL_COUNT){
			actualAdcChannel = 0;
			endOfSequenceFlag = true;
		}
		
	}else if (ADC1->ISR & ADC_ISR_OVR){
		
		ADC1->ISR |= ADC_ISR_OVR;
		ovrCounter++;
		
	}

}

void Analog::adcEnable(){
	
	ADC1->CR |= ADC_CR_ADEN;
	while(true){
		if (ADC1->ISR & ADC_ISR_ADRDY){
			break;
		}
	}
	
}

void Analog::adcStart(){
	
	ADC1->CR |= ADC_CR_ADSTART;
	
}

bool Analog::adcSequenceIsComplete(){

	if (endOfSequenceFlag == false){
		return false;
	}else{
		endOfSequenceFlag = false;
		return true;
	}
	
}

uint32_t Analog::getVccMillivolts(){
	
	uint32_t result = ADC_MAX_CODE; 
	
	result *= VREFINT_VOLTAGE_MILLIVOLTS;
	
	result /= adcData[ADC_CHANNEL_VRefInt];
	
	vccMillivolts = result;
	
	return vccMillivolts;
	
}

uint32_t Analog::getVbatMillivolts(){
	
	uint32_t result = adcData[ADC_CHANNEL_UBat];
	
	result *= vccMillivolts;

	result *= ADC_GAIN_NOM_Ubat;

	result /= ADC_GAIN_DENOM_Ubat;
	
	result /= ADC_MAX_CODE; 
	
	return result;
}

int32_t Analog::getTemperatureDegrees(){
	
	float temperature = (float)(tsense2Value - tsense1Value) / (float)(tsenseCal2Value - tsenseCal1Value) * (float)(adcData[ADC_CHANNEL_TSensor] - tsenseCal1Value) + (float)tsense1Value;
	return (int32_t)temperature;
}






