# XF Port - Active Qt

This port folder contains specific classes for the _Active Qt_
XF port.

# Classes used by the _Active Qt_ Port

| Class name | File location | Define to set |
|--|--|--|
| XFTimeoutManagerDefault | xf/port/default/timeoutmanager-default.cpp | USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION |
| XFDispatcherActiveDefault | xf/port/default/dispatcher-active.cpp | USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION |
| XF | xf/port/idf-qt/xf.cpp | USE_XF_PORT_IDF_QT_XF_IMPLEMENTATION |
| XFMutexPort | xf/port/idf-qt/mutex.cpp | USE_XF_PORT_IDF_QT_MUTEX_IMPLEMENTATION |
| XFThreadPort | xf/port/idf-qt/thread.cpp | USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION |
| XFEventQueuePort | xf/port/idf-qt/eventqueue.cpp | USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION |
| Port Functions | xf/port/idf-qt/port-functions.cpp | USE_XF_PORT_IDF_QT_PORT_FUNCTIONS_IMPLEMENTATION |
| XFResourceFactoryPort | xf/port/active-qt/resourcefactory.cpp | USE_XF_PORT_ACTIVE_QT_RESOURCE_FACTORY_IMPLEMENTATION |

# Example _config/xf-config.h_ File
```c++
// Default implementations
#define USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION            1
#define USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION         1

// Take all the port classes from the IDF_QT port expect...
#define USE_XF_PORT_IDF_QT_XF_IMPLEMENTATION                    1
#define USE_XF_PORT_IDF_QT_MUTEX_IMPLEMENTATION                 1
#define USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION                1
#define USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION           1
#define USE_XF_PORT_IDF_QT_PORT_FUNCTIONS_IMPLEMENTATION        1

// ... the resource factory. Must provide active dispatchers!
#define USE_XF_PORT_ACTIVE_QT_RESOURCE_FACTORY_IMPLEMENTATION   1

#include "idf-qt/eventqueue.h"
```