/*
 * ButtonController.cpp
 *
 *  Created on: 25 mars 2019
 *      Author: Yan Michellod
 */

#include <ButtonController.h>

ButtonController::ButtonController() {
	// TODO Auto-generated constructor stub

}

ButtonController::~ButtonController() {
	// TODO Auto-generated destructor stub
}

void ButtonController::onIrq() {
}

bool ButtonController::registerCallback(
		ButtonsControllerCallbackProvider* callbackProvider,
		ButtonsControllerCallbackProvider::CallbackMethod callbackMethod) {
	provider = callbackProvider;
	callback = callbackMethod;
}
