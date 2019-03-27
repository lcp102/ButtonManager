/*
 * ButtonController.cpp
 *
 *  Created on: 25 mars 2019
 *      Author: Yan Michellod
 */

#include <ButtonController.h>
#include "event/events.h"
#include "event/evbuttonirq.h"
#include "trace.h"


ButtonController::ButtonController() {
	_currentState = STATE_INITIAL;
	callback = nullptr;
	provider = nullptr;
	state[0] = (ButtonController::GPIO_PinState)HAL_GPIO_ReadPin(BUTTON0_GPIO_Port, BUTTON0_Pin);
	state[1] = (ButtonController::GPIO_PinState)HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
	state[2] = (ButtonController::GPIO_PinState)HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
	state[3] = (ButtonController::GPIO_PinState)HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
}

ButtonController::~ButtonController() {
	// TODO Auto-generated destructor stub
}

void ButtonController::onIrq() {
	Trace::out("button interrupt in Controller");
	GEN(evButtonIrq());
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

void ButtonController::checkButtons() {
	// CHECK BUTTON 0
	if (state[0] != (ButtonController::GPIO_PinState) HAL_GPIO_ReadPin(BUTTON0_GPIO_Port, BUTTON0_Pin)){
		// BUTTON 0 has changed
		state[0] = (ButtonController::GPIO_PinState) HAL_GPIO_ReadPin(BUTTON0_GPIO_Port, BUTTON0_Pin);
		// check if is release or pushed
		if(state[0] == GPIO_PIN_RESET){
			//button pushed
			(provider->*callback)(0, true);
		}
		else{
			//button released
			(provider->*callback)(0, false);
		}
	}
	// CHECK BUTTON 1
	if (state[1] != (ButtonController::GPIO_PinState)HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin)){
		// BUTTON 1 has changed
		state[1] = (ButtonController::GPIO_PinState)HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
		// check if is release or pushed
		if(state[1] == GPIO_PIN_RESET){
			//button pushed
			(provider->*callback)(1, true);
		}
		else{
			//button released
			(provider->*callback)(1, false);
		}
	}
	// CHECK BUTTON 2
	if (state[2] != (ButtonController::GPIO_PinState)HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin)){
		// BUTTON 2 has changed
		state[2] = (ButtonController::GPIO_PinState)HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
		// check if is release or pushed
		if(state[2] == GPIO_PIN_RESET){
			//button pushed
			(provider->*callback)(2, true);
		}
		else{
			//button released
			(provider->*callback)(2, false);
		}
	}
	// CHECK BUTTON 3
	if (state[3] != (ButtonController::GPIO_PinState)HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin)){
		// BUTTON 3 has changed
		state[3] = (ButtonController::GPIO_PinState)HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
		// check if is release or pushed
		if(state[3] == GPIO_PIN_RESET){
			//button pushed
			(provider->*callback)(3, true);
		}
		else{
			//button released
			(provider->*callback)(3, false);
		}
	}
}

XFEventStatus ButtonController::processEvent() {
	XFEventStatus status = XFEventStatus::Unknown;
	controllerState _oldState = _currentState;

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
			scheduleTimeout(evButtonIrqId , 100);

			_currentState = STATE_DEBOUNCE;

			status = XFEventStatus::Consumed;
		}
		break;
	}
	case STATE_DEBOUNCE:
	{
		if(getCurrentEvent()->getEventType() == XFEvent::Timeout){
			Trace::out("Debounced");

			_currentState = STATE_CHECK_BUTTON;

			status = XFEventStatus::Consumed;
		}
		break;
	}
	default:
		break;
	}
	if(_oldState != _currentState){
		switch(_currentState){
		case STATE_CHECK_BUTTON:{
			break;
		}
		case STATE_DEBOUNCE:{
			checkButtons();
			break;
		}
		default:
			break;
		}
	}
	return status;
}
