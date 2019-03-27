/*
 * Factory.cpp
 *
 *  Created on: 24 mars 2019
 *      Author: Yan Michellod
 */

#include <app/factory.h>
#include "xf/xf.h"
#include "trace/trace.h"
#include "xf/port/default/resourcefactory-default.h"
#include "platform/f7-disco-gcc/board/ButtonController.h"
 using namespace app;

void Factory_initialize(){
	app::Factory::initialize();
	Trace::initialize();
}
void Factory_build(){
	app::Factory::build();
}

app::ButtonEventsLogger* app::Factory::logger = nullptr;


Factory::Factory() {
}

Factory::~Factory() {
	delete app::Factory::logger;
}

void Factory::initialize() {
	if(app::Factory::logger == nullptr){
		app::Factory::logger = new ButtonEventsLogger();
	}
}

void Factory::build() {

	//start the xf
	XFResourceFactoryDefault::getInstance()->getDefaultDispatcher()->start();
	app::Factory::logger->startBehavior();
	ButtonController::getInstance()->startBehavior();
}

ButtonEventsLogger* Factory::getLogger() {
	return app::Factory::logger;
}

