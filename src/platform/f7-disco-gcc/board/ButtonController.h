/*
 * ButtonController.h
 *
 *  Created on: 25 mars 2019
 *      Author: Yan Michellod
 */

#ifndef BUTTONCONTROLLER_H_
#define BUTTONCONTROLLER_H_

#include "interface/buttonirq.h"
#include "interface/buttonscontrollercallbackprovider.h"
#include "xf/behavior.h"
#include "stm32f7xx_hal.h"

class XFEventStatus;
class evButtonIrq;

class ButtonController : public interface::ButtonsControllerCallbackProvider,
						 public interface::ButtonIrq,
						 public XFBehavior
{
public:
	ButtonController();
	virtual ~ButtonController();

	static ButtonController& getInstance();     ///< Returns a pointer to the single instance of the class.

	virtual void onIrq();	///< @brief Called by the ISR.

	/**
	* @brief Registers a callback method with its called pointer (callback provider).
	*
	* @return Returns true of the callback provider could be registered, otherwise false.
	*/
	virtual bool registerCallback(ButtonsControllerCallbackProvider * callbackProvider,
	                              ButtonsControllerCallbackProvider::CallbackMethod callbackMethod);

protected:

	void checkButtons();
	/**
	* Executes the current event in its implemented behavior.
	* This method needs to be overridden to implement the
	* behavior (i.e. state machine) needed.
	*/
	virtual XFEventStatus processEvent();

	// enum of the state
    typedef enum
    {
    	STATE_UNKWNOWN = 0 ,
    	STATE_INITIAL = 1,
		STATE_CHECK_BUTTON = 2,
    	STATE_DEBOUNCE = 3
    }controllerState;

    controllerState _currentState;


private:
	ButtonsControllerCallbackProvider* provider;
	ButtonsControllerCallbackProvider::CallbackMethod callback;
	GPIO_PinState state [4];
	evButtonIrq* ev;

};

#endif /* BUTTONCONTROLLER_H_ */
