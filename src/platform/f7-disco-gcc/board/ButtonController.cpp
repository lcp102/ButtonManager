/*
 * ButtonController.cpp
 *
 *  Created on: 25 mars 2019
 *      Author: Yan Michellod
 */

#include <ButtonController.h>
#include "event/events.h"


ButtonController::ButtonController() {
	_currentState = STATE_INITIAL;
	Button0Pressed = false;
	Button1Pressed = false;
	Button2Pressed = false;
	Button3Pressed = false;
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
	return true;
}

ButtonController* ButtonController::getInstance() {
	static ButtonController* ButtonControllerInstance = nullptr;
	if(ButtonControllerInstance == nullptr){
		ButtonControllerInstance = new ButtonController();
	}
	return ButtonControllerInstance;
}

void ButtonController::setPushedButton(uint16_t GPIO_Pin) {
	switch(GPIO_Pin){
	case PI2:
	}
}

XFEventStatus ButtonController::processEvent() {
	XFEventStatus status = XFEventStatus::Unknown;

	switch(_currentState){
	case STATE_INITIAL:
	{
		if(getCurrentEvent()->getEventType() == XFEvent::Initial){
			GEN(XFNullTransition());

			_currentState = STATE_CHECK_BUTTON;

			status = XFEventStatus::Consumed;
		}
		break;
	}
	case STATE_CHECK_BUTTON:
	{
		if( getCurrentEvent()->getEventType() == XFEvent::Event && getCurrentEvent()->getId() == evButtonIrqId ){
			scheduleTimeout(0, 100);

			_currentState = STATE_DEBOUNCE;

			status = XFEventStatus::Consumed;
		}
		break;
	}
	case STATE_DEBOUNCE:
	{
		if(getCurrentEvent()->getEventType() == XFEvent::Timeout){
			(provider->*callback)(0, true);

			_currentState = STATE_CHECK_BUTTON;

			status = XFEventStatus::Consumed;
		}
		break;
	}
	default:
		break;
	}
	return status;
}
