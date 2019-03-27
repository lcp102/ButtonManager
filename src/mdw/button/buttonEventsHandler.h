/*
 * buttonEventsHandler.h
 *
 *  Created on: 27 mars 2019
 *      Author: Yan Michellod
 */

#ifndef BUTTONEVENTSHANDLER_H_
#define BUTTONEVENTSHANDLER_H_

#include "list"

class ButtonsControllerCallbackProvider;
class ButtonEventsHandlerSubject;
class ButtonEventsObserver;

using namespace interface;

namespace button {

class ButtonEventsHandler : public ButtonsControllerCallbackProvider,
							public ButtonEventsHandlerSubject
{
public:
	ButtonEventsHandler();
	virtual ~ButtonEventsHandler();
	virtual ButtonEventsHandler* getInstance();
	virtual bool subscribe(ButtonEventsHandlerObserver * observer);			    ///< @brief Registers a new observer. Returns true on success.
	virtual void unsubscribe(ButtonEventsHandlerObserver * observer);	        ///< @brief Un-subscribes a registered observer.
	virtual void onButtonChanged(uint16_t buttonIndex, bool pressed);					///< @brief callBack method

protected:
	virtual void notifyButtonShortPressed(ButtonIndex buttonIndex);	            ///< @brief Notifies observers about a button short pressed.
    virtual void notifyButtonLongPressed(ButtonIndex buttonIndex);              ///< @brief Notifies observers about a button long pressed.

private:
    typedef std::list<ButtonEventsHandlerObserver *> ObserverList;		///< Type used for the _timeouts property.
    ObserverList observers;							///< Container holding timeouts to manage.

};

} /* namespace button */

#endif /* BUTTONEVENTSHANDLER_H_ */
