/*
 * buttonEventsLogger.cpp
 *
 *  Created on: 24 mars 2019
 *      Author: Yan Michellod
 */

#include <app/buttonEventsLogger.h>
#include "config/trace-config.h"
#include "trace/trace.h"
#include <stdio.h>
#include "event/events.h"
#include "event/evbuttonpressed.h"

using namespace app;

ButtonEventsLogger::ButtonEventsLogger() {
	_currentState = STATE_INITIAL;
	_buttonIndex = 10;
}

ButtonEventsLogger::~ButtonEventsLogger() {
	// TODO Auto-generated destructor stub
}

void ButtonEventsLogger::onButtonShortPressed(ButtonIndex buttonIndex) {
	_buttonIndex = buttonIndex;
	isShort = true;
	GEN(evButtonPressed());
}

void ButtonEventsLogger::onButtonLongPressed(ButtonIndex buttonIndex) {
	_buttonIndex = buttonIndex;
	isShort = false;
	GEN(evButtonPressed());
}

XFEventStatus ButtonEventsLogger::processEvent() {
	XFEventStatus status = XFEventStatus::Unknown;

	switch(_currentState){

	case STATE_INITIAL :
	{
		if(getCurrentEvent()->getEventType() == XFEvent::Initial){
			GEN(XFNullTransition());
			onButtonLongPressed(1);
			status = XFEventStatus::Consumed;

			_currentState = STATE_WAIT;
		}

		break;
	}

	case STATE_WAIT:
	{
		if(getCurrentEvent()->getEventType() == XFEvent::NullTransition){
			_currentState = STATE_WAIT;
		}

		else if(getCurrentEvent()->getEventType() == XFEvent::Event && getCurrentEvent()->getId() == evButtonPressedId ){
			GEN(XFNullTransition);

			if(isShort){
				_currentState = STATE_SHORTPRESSED;
			}
			else{
				_currentState = STATE_LONGPRESSED;
			}
			status = XFEventStatus::Consumed;
		}
		break;
	}
	case STATE_SHORTPRESSED:
	{
		if(getCurrentEvent()->getEventType() == XFEvent::NullTransition){
			Trace::out("ButtonEventsLogger : Button %d short pressed",_buttonIndex);

			_currentState = STATE_WAIT;

			status = XFEventStatus::Consumed;

			GEN(XFNullTransition);
		}
		break;
	}
	case STATE_LONGPRESSED:
	{
		if(getCurrentEvent()->getEventType() == XFEvent::NullTransition){
			GEN(XFNullTransition);

			Trace::out("ButtonEventsLogger : Button %d long pressed",_buttonIndex);

			_currentState = STATE_WAIT;

			status = XFEventStatus::Consumed;
			onButtonShortPressed(2);

		}
		break;
	}

	default:
		break;

	}


	return status;
}
