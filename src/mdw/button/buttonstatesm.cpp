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


ButtonStateSM::ButtonStateSM() {
	_currentState = STATE_INITIAL;
}

ButtonStateSM::~ButtonStateSM() {

}

void ButtonStateSM::setNotified(ButtonEventsHandler* notified) {
	_notified = notified;
}

void ButtonStateSM::setButtonIndex(ButtonIndex index) {
	_buttonIndex = index;
}

void ButtonStateSM::buttonPressed() {
	GEN(evButtonPressed());
}

void ButtonStateSM::buttonReleased() {
	GEN(evButtonReleased);
}

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
			unscheduleTimeout(EventIds::evButtonPressedId);
			_notified->notifyButtonShortPressed(_buttonIndex);
			break;
		}
		case STATE_BUTTON_LONG_PRESSED:
		{
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
