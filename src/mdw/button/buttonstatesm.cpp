/*
 * buttonstatesm.cpp
 *
 *  Created on: 29 mars 2019
 *      Author: Yan Michellod
 */

#include <buttonstatesm.h>
#include "event/evbuttonpressed.h"
#include "event/evbuttonreleased.h"
#include "event/events.h"
#include "buttonEventsHandler.h"


/**
 * @brief Constructor of ButtonStateSM
 */
ButtonStateSM::ButtonStateSM() {
	_currentState = STATE_INITIAL;
}

/**
 * @brief Destructor of ButtonStateSM
 */
ButtonStateSM::~ButtonStateSM() {

}

/**
 * @brief Set the object to notify
 */
void ButtonStateSM::setNotified(ButtonEventsHandler* notified) {
	_notified = notified;
}

/**
 * @brief Set the index of the button
 */
void ButtonStateSM::setButtonIndex(ButtonIndex index) {
	_buttonIndex = index;
}

/**
 * @brief launch a event evButtonPressed in the state machine
 */
void ButtonStateSM::buttonPressed() {
	GEN(evButtonPressed());
}

/**
 * @brief launch a event evButtonReleased in the state machine
 */
void ButtonStateSM::buttonReleased() {
	GEN(evButtonReleased);
}

/**
 * @brief processing state machine
 */
XFEventStatus ButtonStateSM::processEvent() {
	XFEventStatus status = XFEventStatus::Unknown;
	handlerState _oldState = _currentState;

	switch(_currentState){// BEGIN STATE CHANGE
	case STATE_INITIAL:
	{
		if(getCurrentEvent()->getEventType() == XFEvent::Initial){
			_currentState = STATE_WAIT_BUTTON_PRESSED;

			status = XFEventStatus::Consumed;
		}
		break;
	}
	case STATE_WAIT_BUTTON_PRESSED:
	{
		if( getCurrentEvent()->getEventType() == XFEvent::Event && getCurrentEvent()->getId() == EventIds::evButtonPressedId){
			_currentState = STATE_BUTTON_PRESSED;

			status = XFEventStatus::Consumed;
		}
		break;
	}
	case STATE_BUTTON_PRESSED:
	{
		if(getCurrentEvent()->getEventType() == XFEvent::Event && getCurrentEvent()->getId() == EventIds::evButtonReleasedId){
			GEN(XFNullTransition());

			_currentState = STATE_BUTTON_SHORT_PRESSED;

			status = XFEventStatus::Consumed;
		}
		else if(getCurrentEvent()->getEventType() == XFEvent::Timeout){
			GEN(XFNullTransition());

			_currentState = STATE_BUTTON_LONG_PRESSED;

			status = XFEventStatus::Consumed;
		}
		break;
	}
	case STATE_BUTTON_SHORT_PRESSED:
	{
		if(getCurrentEvent()->getEventType() == XFEvent::NullTransition){
			GEN(XFNullTransition());

			_currentState = STATE_WAIT_BUTTON_PRESSED;

			status = XFEventStatus::Consumed;
		}
		break;
	}
	case STATE_BUTTON_LONG_PRESSED:
	{
		if(getCurrentEvent()->getEventType() == XFEvent::NullTransition){
			GEN(XFNullTransition());

			_currentState = STATE_WAIT_BUTTON_PRESSED;

			status = XFEventStatus::Consumed;
		}
		break;
	}
	default:
		break;
	}
	// END STATE CHANGE
	// BEGIN ACTION ON ENTRY
	if(_oldState != _currentState){
		switch(_currentState){
		case STATE_BUTTON_PRESSED:
		{
			// start timer to detect a long pressed
			scheduleTimeout(EventIds::evButtonPressedId,1000);
			break;
		}
		case STATE_BUTTON_SHORT_PRESSED:
		{
			// unschedule timeout because short pressed
			unscheduleTimeout(EventIds::evButtonPressedId);
			// notify the handler that the button was short pressed
			_notified->notifyButtonShortPressed(_buttonIndex);
			break;
		}
		case STATE_BUTTON_LONG_PRESSED:
		{
			// notify the handler that the button is long pressed
			_notified->notifyButtonLongPressed(_buttonIndex);
			break;
		}
		default:
			break;
		}
	}
	// END ACTION ON ENTRY
	return status;

}
