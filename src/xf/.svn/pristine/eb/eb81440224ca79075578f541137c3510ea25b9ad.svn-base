#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION != 0)

#include <assert.h>
#include <string.h>
#include "thread.h"

#if !defined(XFTHREAD_DEFAULT_STACK_SIZE)
    #define XFTHREAD_DEFAULT_STACK_SIZE	256
#endif

XFThreadPort::XFThreadPort(interface::XFThreadEntryPointProvider * pProvider,
                           interface::XFThread::EntryMethodBody entryMethod,
                           const char * threadName,
                           const uint32_t stackSize /* = 0 */)
{
    uint32_t threadStackSize = stackSize;

    _pEntryMethodProvider = pProvider;
    _entryMethod = entryMethod;

    const QString name(threadName);
    if (!name.isEmpty())
    {
        setObjectName(name);
    }

    if (threadStackSize == 0)
    {
        threadStackSize = XFTHREAD_DEFAULT_STACK_SIZE;
    }

    setStackSize(threadStackSize);
}

void XFThreadPort::run()
{
    // Call the entry point method with received provider
    (this->_pEntryMethodProvider->*this->_entryMethod)(this);
}

void XFThreadPort::start()
{
    QThread::start();
}

void XFThreadPort::stop()
{
    QThread::terminate();
    QThread::wait();	// Wait on thread to terminate
}


void XFThreadPort::setPriority(XFThreadPriority priority)
{
    auto prio = QThread::NormalPriority;
    switch (priority)
    {
    case XF_THREAD_PRIO_LOW:
        prio = QThread::LowPriority;
        break;
    case XF_THREAD_PRIO_HIGH:
        prio = QThread::HighPriority;
        break;
    default:
        break;
    }

    QThread::setPriority(prio);
}

XFThreadPriority XFThreadPort::getPriority() const
{
    const auto prio = QThread::priority();
    XFThreadPriority priority = XF_THREAD_PRIO_UNKNOWN;

    switch (prio)
    {
    case QThread::LowPriority:
        priority = XF_THREAD_PRIO_LOW;
        break;
    case QThread::NormalPriority:
        priority = XF_THREAD_PRIO_NORMAL;
        break;
    case QThread::HighPriority:
        priority = XF_THREAD_PRIO_HIGH;
        break;
    default:
        break;
    }

    return priority;
}

void XFThreadPort::delay(uint32_t milliseconds)
{
    QThread::msleep(milliseconds);
}

#endif // USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION
