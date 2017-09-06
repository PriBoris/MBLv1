
#include "UI.h"


#include "Ports.h"


#define LED_RED_GPIO_PIN	GPIOA, 10
#define LED_GREEN_GPIO_PIN	GPIOA, 9

#define BTN_MINUS_GPIO_PIN	GPIOB, 14
#define BTN_PLUS_GPIO_PIN	GPIOB, 15
#define BTN_CTRL_GPIO_PIN	GPIOA, 8

void UI::init(){

	Ports::initOutput(
		LED_RED_GPIO_PIN,
		Ports::GPIO_PushPull,
		Ports::GPIO_LowSpeed,
		Ports::Set
		);

	Ports::initOutput(
		LED_GREEN_GPIO_PIN,
		Ports::GPIO_PushPull,
		Ports::GPIO_LowSpeed,
		Ports::Set
		);

	Ports::initInput(
		BTN_MINUS_GPIO_PIN,
		Ports::GPIO_PullDown
		);	

	Ports::initInput(
		BTN_PLUS_GPIO_PIN,
		Ports::GPIO_PullDown
		);	

	Ports::initInput(
		BTN_CTRL_GPIO_PIN,
		Ports::GPIO_PullDown
		);	



}

void UI::ledRed(){

	Ports::outputReset(LED_RED_GPIO_PIN);
	Ports::outputSet(LED_GREEN_GPIO_PIN);

}

void UI::ledGreen(){

	Ports::outputSet(LED_RED_GPIO_PIN);
	Ports::outputReset(LED_GREEN_GPIO_PIN);

}

void UI::ledYellow(){

	Ports::outputReset(LED_RED_GPIO_PIN);
	Ports::outputReset(LED_GREEN_GPIO_PIN);

}

void UI::ledOff(){

	Ports::outputSet(LED_RED_GPIO_PIN);
	Ports::outputSet(LED_GREEN_GPIO_PIN);

}

bool UI::btnPlusIsPushed(){
	return Ports::inputIsSet(BTN_PLUS_GPIO_PIN);
}

bool UI::btnMinusIsPushed(){
	return Ports::inputIsSet(BTN_MINUS_GPIO_PIN);
}

bool UI::btnCtrlIsPushed(){
	return Ports::inputIsSet(BTN_CTRL_GPIO_PIN);	
}



