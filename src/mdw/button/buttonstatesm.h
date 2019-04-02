/*
 * buttonstatesm.h
 *
 *  Created on: 29 mars 2019
 *      Author: Yan Michellod
 */

#ifndef BUTTONSTATESM_H_
#define BUTTONSTATESM_H_

#include "xf/behavior.h"
#include "interface/buttoneventshandlerobserver.h"

class ButtonEventsHandler;

class ButtonStateSM : public XFBehavior
{
public:
	typedef interface::ButtonEventsHandlerObserver::ButtonIndex ButtonIndex;

	ButtonStateSM();
	virtual ~ButtonStateSM();
	void setNotified(ButtonEventsHandler* notified);
	void setButtonIndex(ButtonIndex index);
	void buttonPressed();
	void buttonReleased();

protected:
    /**
     * Executes the current event in its implemented behavior.
     * This method needs to be overridden to implement the
     * behavior (i.e. state machine) needed.
     */
    virtual XFEventStatus processEvent();

    typedef enum
    {
    	STATE_UNKWNOWN = 0 ,
    	STATE_INITIAL = 1,
		STATE_WAIT_BUTTON_PRESSED = 2,
    	STATE_BUTTON_PRESSED = 3,
		STATE_BUTTON_SHORT_PRESSED = 4,
		STATE_BUTTON_LONG_PRESSED = 5
    }handlerState;


private:
    ButtonEventsHandler* _notified;
    handlerState _currentState;
    ButtonIndex  _buttonIndex;

};

#endif /* BUTTONSTATESM_H_ */
