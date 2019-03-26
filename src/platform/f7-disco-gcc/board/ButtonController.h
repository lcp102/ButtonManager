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

class ButtonController : public interface::ButtonIrq,
						 public interface::ButtonsControllerCallbackProvider
{
public:
	ButtonController();
	virtual ~ButtonController();

protected:
	virtual void onIrq();	///< @brief Called by the ISR.
	/**
	* @brief Registers a callback method with its called pointer (callback provider).
	*
	* @return Returns true of the callback provider could be registered, otherwise false.
	*/
	virtual bool registerCallback(ButtonsControllerCallbackProvider * callbackProvider,
	                              ButtonsControllerCallbackProvider::CallbackMethod callbackMethod);

private:
	ButtonsControllerCallbackProvider* provider;
	ButtonsControllerCallbackProvider::CallbackMethod callback;
};

#endif /* BUTTONCONTROLLER_H_ */
