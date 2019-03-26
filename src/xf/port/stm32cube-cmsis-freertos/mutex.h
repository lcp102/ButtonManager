#ifndef XF_PORT_STM32CUBE_CMSIS_FREERTOS_MUTEX_H
#define XF_PORT_STM32CUBE_CMSIS_FREERTOS_MUTEX_H

#include <config/xf-config.h>

#if (USE_XF_PORT_STM32CUBE_CMSIS_FREERTOS_MUTEX_IMPLEMENTATION != 0)

#include <stdint.h>
#include <cmsis_os.h>
#include "xf/interface/mutex.h"

class XFMutexPort : public interface::XFMutex
{
public:
	XFMutexPort();
	virtual ~XFMutexPort();

	virtual void lock();
	virtual void unlock();

	virtual bool tryLock(int32_t timeout = 0);

protected:
	osMutexDef_t _mutexDefinition;
	osMutexId _mutexId;
};

#endif // USE_XF_PORT_STM32CUBE_CMSIS_FREERTOS_MUTEX_IMPLEMENTATION
#endif // XF_PORT_STM32CUBE_CMSIS_FREERTOS_MUTEX_H
