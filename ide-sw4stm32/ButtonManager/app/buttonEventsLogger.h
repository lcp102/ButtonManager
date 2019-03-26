/*
 * buttonEventsLogger.h
 *
 *  Created on: 24 mars 2019
 *      Author: Yan Michellod
 */

#ifndef BUTTONEVENTSLOGGER_H_
#define BUTTONEVENTSLOGGER_H_

#include "interface/buttoneventshandlerobserver.h"



class ButtonEventsLogger : public interface::ButtonEventsHandlerObserver
{
public:
	ButtonEventsLogger();
	virtual ~ButtonEventsLogger();

protected:
	virtual void onButtonShortPressed(ButtonIndex buttonIndex);         ///< @brief Called by the subject upon a button short pressed.
    virtual void onButtonLongPressed(ButtonIndex buttonIndex);          ///< @brief Called by the subject upon a button long pressed.

};

#endif /* BUTTONEVENTSLOGGER_H_ */
