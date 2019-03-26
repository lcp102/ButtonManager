/*
 * Factory.cpp
 *
 *  Created on: 24 mars 2019
 *      Author: Yan Michellod
 */

#include <app/factory.h>
#include "xf/xf.h"
#include "trace/trace.h"
 using namespace app;

void Factory_initialize(){
	app::Factory::initialize();
	Trace::initialize();
}
void Factory_build(){
	app::Factory::build();
}

ButtonEventsLogger* app::Factory::logger = nullptr;


Factory::Factory() {
}

Factory::~Factory() {
	delete logger;
}

void Factory::initialize() {
	if(!app::Factory::logger){
		app::Factory::logger = new ButtonEventsLogger();
	}
	// initilize the XF
}

void Factory::build() {

	//start the xf
	XF_exec();
	logger->startBehavior();
}

ButtonEventsLogger* Factory::getLogger() {
	return app::Factory::logger;
}

