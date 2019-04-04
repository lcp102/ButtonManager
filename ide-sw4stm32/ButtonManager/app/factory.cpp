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

/**
 * @brief method call by C compiler
 * Initialize Factory calling it C++ version
 */
void Factory_initialize(){
	app::Factory::initialize();
}

/**
 * @brief method call by C compiler
 * Build Factory calling it C++ version
 */
void Factory_build(){
	app::Factory::build();
}

// static attribute
app::ButtonEventsLogger* app::Factory::logger = nullptr;

/**
 * @brief Constructor of Factory
 */
app::Factory::Factory() {
}

/**
 * @brief Destructor of Factory
 */
app::Factory::~Factory() {
	delete app::Factory::logger;
}

/**
 * @brief Initialize Factory
 * Create all object needed for the project
 */
void app::Factory::initialize() {

}

/**
 * @brief Build Factory
 * Bind object and start state machine of behavioral class
 */
void app::Factory::build() {

	//bind class
	ButtonEventsHandler::getInstance()->subscribe(app::Factory::getLogger());
	ButtonController::getInstance()->registerCallback(ButtonEventsHandler::getInstance(),
			(interface::ButtonsControllerCallbackProvider::CallbackMethod)&ButtonEventsHandler::onButtonChanged);

	//start the behavioral classes
	XFResourceFactoryDefault::getInstance()->getDefaultDispatcher()->start();
	app::Factory::getLogger()->startBehavior();
	ButtonController::getInstance()->startBehavior();
	ButtonEventsHandler::getInstance()->startInternalSM();
}

/**
 * @brief
 * @return return an instance of ButtonEventsLogger
 */
app::ButtonEventsLogger* app::Factory::getLogger() {
	if(app::Factory::logger == nullptr){
		app::Factory::logger = new ButtonEventsLogger();
	}
	return app::Factory::logger;
}

