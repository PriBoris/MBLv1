
#ifndef UI_H
#define UI_H


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


#endif //UI_H

