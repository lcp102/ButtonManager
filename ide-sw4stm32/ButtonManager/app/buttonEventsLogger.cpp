/*
 * buttonEventsLogger.cpp
 *
 *  Created on: 24 mars 2019
 *      Author: Yan Michellod
 */

#include <app/buttonEventsLogger.h>
#include "config/trace-config.h"
#include "trace/trace.h"
#include <stdio.h>

ButtonEventsLogger::ButtonEventsLogger() {
	// TODO Auto-generated constructor stub

}

ButtonEventsLogger::~ButtonEventsLogger() {
	// TODO Auto-generated destructor stub
}

void ButtonEventsLogger::onButtonShortPressed(ButtonIndex buttonIndex) {
	Trace::out("ButtonEventsLogger : Button %d short pressed",buttonIndex);
}

void ButtonEventsLogger::onButtonLongPressed(ButtonIndex buttonIndex) {
	Trace::out("ButtonEventsLogger : Button %d long pressed",buttonIndex);
}
