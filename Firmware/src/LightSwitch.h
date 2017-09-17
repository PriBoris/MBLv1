

#ifndef LIGHT_SWITCH_H
#define LIGHT_SWITCH_H

/**
	@ingroup BL
	@{
	@brief Routines for connecting battery to the light block
*/
class LightSwitch{
private:
	

public:

	/**
	Initialize
	*/

	static void init(void);

	/**
	Connect
	*/
	static void setOn(void);

	/**
	Disconnect
	*/
	static void setOff(void);


};
/**
	@}
*/



#endif //LIGHT_SWITCH_H
