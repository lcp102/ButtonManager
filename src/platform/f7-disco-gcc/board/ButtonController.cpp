/*
 * ButtonController.cpp
 *
 *  Created on: 25 mars 2019
 *      Author: Yan Michellod
 */

#include <ButtonController.h>

ButtonController::ButtonController() {
	_currentState = STATE_INITIAL;
}

ButtonController::~ButtonController() {
	// TODO Auto-generated destructor stub
}

void ButtonController::onIrq() {
}

bool ButtonController::registerCallback(
		ButtonsControllerCallbackProvider* callbackProvider,
		ButtonsControllerCallbackProvider::CallbackMethod callbackMethod) {
	provider = callbackProvider;
	callback = callbackMethod;
}

XFEventStatus ButtonController::processEvent() {
	XFEventStatus status = XFEventStatus::Unknown;

	switch(_currentState){
	case STATE_INITIAL:
	}
	return status;
}
