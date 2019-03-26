/*
 * ButtonController.h
 *
 *  Created on: 25 mars 2019
 *      Author: Yan Michellod
 */

#ifndef BUTTONCONTROLLER_H_
#define BUTTONCONTROLLER_H_

#include "interface/buttonirq.h"
#include "interface/buttonscontrollercallbackcaller.h"
#include "xf/behavior.h"
#include "xf/eventstatus.h"

class ButtonController : public interface::ButtonsControllerCallbackProvider,
						 public interface::ButtonIrq,
						 public XFBehavior
{
public:
	ButtonController();
	virtual ~ButtonController();

	static ButtonController * getInstance();     ///< Returns a pointer to the single instance of the class.

	virtual void onIrq();	///< @brief Called by the ISR.
	/**
	* @brief Registers a callback method with its called pointer (callback provider).
	*
	* @return Returns true of the callback provider could be registered, otherwise false.
	*/
	virtual bool registerCallback(ButtonsControllerCallbackProvider * callbackProvider,
	                              ButtonsControllerCallbackProvider::CallbackMethod callbackMethod);
	/**
	* Executes the current event in its implemented behavior.
	* This method needs to be overridden to implement the
	* behavior (i.e. state machine) needed.
	*/

protected:

	virtual XFEventStatus processEvent();

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
	bool Button0Pressed;
	bool Button1Pressed;
	bool Button2Pressed;
	bool Button3Pressed;
	bool Button0Irq;
	bool Button1Irq;
	bool Button2Irq;
	bool Button3Irq;


};

#endif /* BUTTONCONTROLLER_H_ */
