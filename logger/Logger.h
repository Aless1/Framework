#ifndef __FRAMEWORK_LOGGER__
#define __FRAMEWORK_LOGGER__

#include "ILogger.h"

using namespace tcore;

#define ASYN_TEMP_SIZE (1024 * 4)

class Logger : public ILogger {
public:
    virtual bool Launch();
    virtual bool Shutdown();

    virtual void LogSyn(char * type, char * log,  char * filename, int line);
    virtual void LogASyn(char * type, char * log,  char * filename, int line);
private:
    char _asyn_log_temp[ASYN_TEMP_SIZE];
};

#endif // __FRAMEWORK_LOGGER__