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


/**
 * @brief Destructor of ButtonEventsHandler
 */
ButtonEventsHandler::~ButtonEventsHandler() {
	for(int i = 0 ; i < 4; i++){
		delete sm[i];
		sm[i] = nullptr;
	}
}

/**
 * @brief
 * @return return an instance of the ButtonEventsHandler
 */
ButtonEventsHandler* ButtonEventsHandler::getInstance() {
	static ButtonEventsHandler ButtonEventsHandlerInstance;
	return &ButtonEventsHandlerInstance;
}

/**
 * @brief add an observer in the list
 * @return return true if success else false
 */
bool ButtonEventsHandler::subscribe(interface::ButtonEventsHandlerObserver* observer) {
	observers.push_front(observer);
	return true;
}

/**
 * @brief delete an observer in the list
 */
void ButtonEventsHandler::unsubscribe(
		interface::ButtonEventsHandlerObserver* observer) {
	for (ObserverList::iterator it = observers.begin();
			             it != observers.end(); /*Do not increment here!*/)
			{
				if(*it == observer){
					observers.erase(it);
					break;
				}
				else{
					it++;;
				}
			}
}

/**
 * @brief start the behavior of state machine
 */
void ButtonEventsHandler::startInternalSM() {
	for(int i = 0; i < 4 ; i++){
		sm[i]->startBehavior();
	}
}

/**
 * @brief notify observers about short pressed
 */
void ButtonEventsHandler::notifyButtonShortPressed(ButtonIndex buttonIndex) {
	for(ObserverList::iterator it = observers.begin();
		             it != observers.end(); it++)
		{
			(*it)->onButtonShortPressed(buttonIndex);
		}
}

/**
 * @brief notify observers about long pressed
 */
void ButtonEventsHandler::notifyButtonLongPressed(ButtonIndex buttonIndex) {
	for(ObserverList::iterator it = observers.begin();
	             it != observers.end(); it++)
	{
		(*it)->onButtonLongPressed(buttonIndex);
	}
}

/**
 * @brief advertise state machine about change of button state
 */
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

/**
 * @brief Constructor of ButtonEventsHandler
 */
ButtonEventsHandler::ButtonEventsHandler() {
	sm[0] = new ButtonStateSM();
	sm[1] = new ButtonStateSM();
	sm[2] = new ButtonStateSM();
	sm[3] = new ButtonStateSM();
	// set the class the state machine must notified
	for(int i = 0 ; i < 4; i ++){
		sm[i]->setNotified(this);
		sm[i]->setButtonIndex(i);
	}
}


