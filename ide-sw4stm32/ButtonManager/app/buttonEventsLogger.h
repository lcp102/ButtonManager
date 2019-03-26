/*
 * buttonEventsLogger.h
 *
 *  Created on: 24 mars 2019
 *      Author: Yan Michellod
 */

#ifndef BUTTONEVENTSLOGGER_H_
#define BUTTONEVENTSLOGGER_H_

#include "interface/buttoneventshandlerobserver.h"
#include "xf/behavior.h"

namespace app {

class ButtonEventsLogger : public interface::ButtonEventsHandlerObserver,
						   public XFBehavior
{
public:
	ButtonEventsLogger();
	virtual ~ButtonEventsLogger();

protected:
	virtual void onButtonShortPressed(ButtonIndex buttonIndex);         ///< @brief Called by the subject upon a button short pressed.
    virtual void onButtonLongPressed(ButtonIndex buttonIndex);          ///< @brief Called by the subject upon a button long pressed.
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
		STATE_WAIT = 2,
    	STATE_SHORTPRESSED = 3,
		STATE_LONGPRESSED =4
    }LoggerState;

    LoggerState _currentState;

private:
    ButtonIndex _buttonIndex;
    bool isShort;

};
}//namespace app
#endif /* BUTTONEVENTSLOGGER_H_ */
