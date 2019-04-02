/*
 * Factory.h
 *
 *  Created on: 24 mars 2019
 *      Author: Yan Michellod
 */

#ifndef FACTORY_H_
#define FACTORY_H_



//
// What is seen only by the C++ compiler
//
#ifdef __cplusplus
namespace app{
	class ButtonEventsLogger;
}

namespace app {

class Factory {
public:
	Factory();
	virtual ~Factory();
	static void initialize(); // initialize all object needed
	static void build(); // initialize relations between objects
	static ButtonEventsLogger* getLogger(); // get the instance of the logger


private:
	static ButtonEventsLogger* logger;
};
}// namespace app
#endif // __cplusplus
//
// What is seen by the C and C++ compiler
//
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void Factory_initialize();
void Factory_build();

#ifdef __cplusplus
}
#endif // __cplusplus
#endif /* FACTORY_H_ */
