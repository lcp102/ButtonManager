/*
 * Factory.cpp
 *
 *  Created on: 24 mars 2019
 *      Author: Yan Michellod
 */

#include <app/factory.h>
#include "xf/xf.h"
#include <cstdint>
#include "trace.h"
#include "xf/port/default/resourcefactory-default.h"
#include "platform/f7-disco-gcc/board/ButtonController.h"
#include "app/buttonEventsLogger.h"
#include "interface/buttonscontrollercallbackprovider.h"
#include "buttonEventsHandler.h"

void Factory_initialize(){
	app::Factory::initialize();
	Trace::initialize();
}
void Factory_build(){
	app::Factory::build();
}


app::ButtonEventsLogger* app::Factory::logger = nullptr;


app::Factory::Factory() {
}

app::Factory::~Factory() {
	delete app::Factory::logger;
}

void app::Factory::initialize() {
	if(app::Factory::logger == nullptr){
		app::Factory::logger = new ButtonEventsLogger();
	}
}

void app::Factory::build() {

	//bind class
	ButtonEventsHandler::getInstance()->subscribe(app::Factory::logger);
	ButtonController::getInstance()->registerCallback(ButtonEventsHandler::getInstance(),
			(interface::ButtonsControllerCallbackProvider::CallbackMethod)&ButtonEventsHandler::onButtonChanged);

	//start the behavioral classes
	XFResourceFactoryDefault::getInstance()->getDefaultDispatcher()->start();
	app::Factory::logger->startBehavior();
	ButtonController::getInstance()->startBehavior();
	ButtonEventsHandler::getInstance()->startInternalSM();
}

app::ButtonEventsLogger* app::Factory::getLogger() {
	return app::Factory::logger;
}

