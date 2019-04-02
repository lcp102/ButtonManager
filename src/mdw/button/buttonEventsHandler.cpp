/*
 * buttonEventsHandler.cpp
 *
 *  Created on: 27 mars 2019
 *      Author: Yan Michellod
 */

#include <buttonEventsHandler.h>
#include "button/buttonstatesm.h"
#include "interface/buttoneventshandlerobserver.h"
#include "event/evbuttonpressed.h"
#include "event/evbuttonreleased.h"

ButtonEventsHandler::~ButtonEventsHandler() {

}

ButtonEventsHandler* ButtonEventsHandler::getInstance() {
	static ButtonEventsHandler ButtonEventsHandlerInstance;
	return &ButtonEventsHandlerInstance;
}

bool ButtonEventsHandler::subscribe(
		interface::ButtonEventsHandlerObserver* observer) {
	observers.push_front(observer);
	return true;
}

void ButtonEventsHandler::unsubscribe(
		interface::ButtonEventsHandlerObserver* observer) {
	for (ObserverList::iterator it = observers.begin();
			             it != observers.end(); /*Do not increment here!*/)
			{
				if(*it == observer){
					observers.erase(it);
					delete *it;
					break;
				}
				else{
					it++;;
				}
			}
}

void ButtonEventsHandler::startInternalSM() {
	for(int i = 0; i < 4 ; i++){
		sm[i]->startBehavior();
	}
}


void ButtonEventsHandler::notifyButtonShortPressed(ButtonIndex buttonIndex) {
	for(ObserverList::iterator it = observers.begin();
		             it != observers.end(); it++)
		{
			(*it)->onButtonShortPressed(buttonIndex);
		}
}

void ButtonEventsHandler::notifyButtonLongPressed(ButtonIndex buttonIndex) {
	for(ObserverList::iterator it = observers.begin();
	             it != observers.end(); it++)
	{
		(*it)->onButtonLongPressed(buttonIndex);
	}
}

void ButtonEventsHandler::onButtonChanged(uint16_t buttonIndex, bool pressed) {
	switch(buttonIndex){
	case 0:
	{
		if(pressed){
			sm[0]->pushEvent(new evButtonPressed());
		}
		else{
			sm[0]->pushEvent(new evButtonReleased());
		}
		break;
	}
	case 1:
	{
		if(pressed){
			sm[1]->pushEvent(new evButtonPressed());
		}
		else{
			sm[1]->pushEvent(new evButtonReleased());
		}
		break;
	}
	case 2:
	{
		if(pressed){
			sm[2]->pushEvent(new evButtonPressed());
		}
		else{
			sm[2]->pushEvent(new evButtonReleased());
		}
		break;
	}
	case 3:
	{
		if(pressed){
			sm[3]->pushEvent(new evButtonPressed());
		}
		else{
			sm[3]->pushEvent(new evButtonReleased());
		}
		break;
	}
	}
}


ButtonEventsHandler::ButtonEventsHandler() {
	sm[0] = new ButtonStateSM();
	sm[1] = new ButtonStateSM();
	sm[2] = new ButtonStateSM();
	sm[3] = new ButtonStateSM();
	for(int i = 0 ; i < 4; i ++){
		sm[i]->setNotified(this);
		sm[i]->setButtonIndex(i);
	}
}


