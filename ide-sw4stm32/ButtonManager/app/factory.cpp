/*
 * Factory.cpp
 *
 *  Created on: 24 mars 2019
 *      Author: Yan Michellod
 */

#include <app/factory.h>
#include "xf/xf.h"
#include "trace/trace.h"


void Factory_initialize(){
	Factory::initialize();
}
void Factory_build(){
	Factory::build();
}

ButtonEventsLogger* Factory::logger = nullptr;
StateMachine01 Factory::_task01(1000, "Say Hello");


Factory::Factory() {
}

Factory::~Factory() {
	delete logger;
}

void Factory::initialize() {
	if(!Factory::logger){
		Factory::logger = new ButtonEventsLogger();
	}
	// initilize the XF
	Trace::initialize();
	XF_initialize(20);
}

void Factory::build() {

	//start the xf
	XF_exec();
    _task01.startBehavior();

}

ButtonEventsLogger* Factory::getLogger() {
	return Factory::logger;
}
