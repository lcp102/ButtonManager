/*
 * buttonEventsHandler.cpp
 *
 *  Created on: 27 mars 2019
 *      Author: Yan Michellod
 */

#include <button/buttonEventsHandler.h>
#include "interface/buttonscontrollercallbackprovider.h"
#include "interface/buttoneventshandlersubject.h"
#include "interface/buttoneventsobserver.h"

namespace button {

ButtonEventsHandler::ButtonEventsHandler() {
}

ButtonEventsHandler::~ButtonEventsHandler() {
	// TODO Auto-generated destructor stub
}

bool ButtonEventsHandler::subscribe(ButtonEventsHandlerObserver* observer) {
	observers.push_front(observer);
}

void ButtonEventsHandler::unsubscribe(ButtonEventsHandlerObserver* observer) {
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


ButtonEventsHandler* ButtonEventsHandler::getInstance() {
	static ButtonEventsHandler ButtonEventsHandlerInstance;
	return &ButtonEventsHandlerInstance;
}

void ButtonEventsHandler::onButtonChanged(uint16_t buttonIndex, bool pressed) {
}

void ButtonEventsHandler::notifyButtonShortPressed(ButtonIndex buttonIndex) {
	for(ObserverList::iterator it = observers.begin();
	             it != observers.end(); it++)
	{
		(*it)->ButtonEventsHandlerObserver::onButtonShortPressed(buttonIndex);
	}
}

void ButtonEventsHandler::notifyButtonLongPressed(ButtonIndex buttonIndex) {
	for(ObserverList::iterator it = observers.begin();
	             it != observers.end(); it++)
	{
		(*it)->ButtonEventsHandlerObserver::onButtonLongPressed(buttonIndex);
	}
}

} /* namespace button */
