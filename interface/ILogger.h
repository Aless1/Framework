#ifndef __FRAMEWORK_ILOGGER__
#define __FRAMEWORK_ILOGGER__

#include "ICM.h"

namespace tcore {
class ILogger : public ICM {
public:
    virtual bool Launch() = 0;
    virtual bool Shutdown() = 0;

    virtual void LogSyn(const char * log) = 0;
    virtual void LogAsyn(const char * log) = 0;

    virtual ~ILogger() {}
};

ILogger * GetLoggerInstance();
}

#define LOG_TEMP_SIZE_MAX 4096

#endif // __FRAMEWORK_ILOGGER__