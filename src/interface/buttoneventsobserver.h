#ifndef INTERFACE_BUTTONEVENTSOBSERVER_H
#define INTERFACE_BUTTONEVENTSOBSERVER_H

namespace interface {

class ButtonEventsObserver
{
public:
	virtual ~ButtonEventsObserver() {}

	virtual void onButtonShortPressed(uint8_t buttonIndex) = 0;
	virtual void onButtonLongPressed(uint8_t buttonIndex) = 0;
    
protected:
    ButtonEventsObserver() {}       ///< Not allowing to instantiate interface
};

} // namespace interface
#endif // INTERFACE_BUTTONEVENTSOBSERVER_H
