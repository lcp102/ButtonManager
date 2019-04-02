/*
 * buttonEventsHandler.h
 *
 *  Created on: 27 mars 2019
 *      Author: Yan Michellod
 */

#ifndef BUTTONEVENTSHANDLER_H_
#define BUTTONEVENTSHANDLER_H_

#include "list"
#include "interface/buttoneventshandlersubject.h"
#include "interface/buttonscontrollercallbackprovider.h"

class ButtonStateSM;


class ButtonEventsHandler : public interface::ButtonEventsHandlerSubject,
							public interface::ButtonsControllerCallbackProvider
{
	friend class ButtonStateSM;
public:
	virtual ~ButtonEventsHandler();
	static ButtonEventsHandler* getInstance();
	virtual bool subscribe(interface::ButtonEventsHandlerObserver * observer);			    ///< @brief Registers a new observer. Returns true on success.
	virtual void unsubscribe(interface::ButtonEventsHandlerObserver * observer);	        ///< @brief Un-subscribes a registered observer.
	void onButtonChanged(uint16_t buttonIndex, bool pressed);
	void startInternalSM();


protected:
	virtual void notifyButtonShortPressed(ButtonIndex buttonIndex);	            ///< @brief Notifies observers about a button short pressed.
    virtual void notifyButtonLongPressed(ButtonIndex buttonIndex);              ///< @brief Notifies observers about a button long pressed.
	ButtonEventsHandler();


private:
    typedef std::list<interface::ButtonEventsHandlerObserver *> ObserverList;		///< Type used for the _timeouts property.
    ObserverList observers;							///< Container holding timeouts to manage.

    ButtonStateSM* sm[4];

};


} /* namespace button */

#endif /* BUTTONEVENTSHANDLER_H_ */
