#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_PORT_STM32CUBE_CMSIS_FREERTOS_MUTEX_IMPLEMENTATION != 0)

#include "mutex.h"

XFMutexPort::XFMutexPort() :
	_mutexId(0)
{
	_mutexId = osMutexCreate(&_mutexDefinition);
	assert(_mutexId);
}

XFMutexPort::~XFMutexPort()
{

}

void XFMutexPort::lock()
{
	assert(_mutexId);
	osStatus status = osMutexWait(_mutexId, osWaitForever);
	assert(status == osOK);
}


void XFMutexPort::unlock()
{
	osStatus status = osMutexRelease(_mutexId);
	assert(status == osOK);
}


bool XFMutexPort::tryLock(int32_t timeout /* = 0 */)
{
	osStatus status = osMutexWait(_mutexId, timeout);
	return (status == osOK) ? true : false;
}

#endif // USE_XF_PORT_STM32CUBE_CMSIS_FREERTOS_MUTEX_IMPLEMENTATION
