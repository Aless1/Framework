#ifndef __FRAMEWORK_ILOGGER__
#define __FRAMEWORK_ILOGGER__

#include "ICM.h"

namespace tcore {
class ILogger : public ICM {
public:
    virtual bool Launch() = 0;
    virtual bool Shutdown() = 0;

    virtual void LogSyn(char * path, char * log,  char * filename, int line) = 0;
    virtual void LogAsyn(char * path, char * log,  char * filename, int line) = 0;

    virtual ~ILogger() {}
};

ILogger * GetLoggerInstance();
}

#endif // __FRAMEWORK_ILOGGER__