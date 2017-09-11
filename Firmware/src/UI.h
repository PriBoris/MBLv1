
#ifndef UI_H
#define UI_H


/**
	@defgroup BL Business Logic
	@brief Hardware independent routines
*/




/**
	@ingroup BL
	@{
	@brief Routines for buttons and indicators
*/
class UI{
private:
public:
	
	static void init();

	static void ledGreen();
	static void ledRed();
	static void ledYellow();
	static void ledOff();

	static bool btnPlusIsPushed();
	static bool btnMinusIsPushed();
	static bool btnCtrlIsPushed();

};
/**
	@}
*/

#endif //UI_H

