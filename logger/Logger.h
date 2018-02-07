#ifndef __FRAMEWORK_LOGGER__
#define __FRAMEWORK_LOGGER__

#include <unordered_map>
#include <string>

#include "ILogger.h"
#include "Thread.h"

#include "LogFile.h"

using namespace tcore;
using namespace std;

#define ASYN_TEMP_QUEUE_SIZE 128

struct logunit {
    long long tick;
    string log;
};

class Logger : public ILogger, public Lib::Thread {
typedef std::unordered_map<const char *, LogFile *> LOGFILE_MAP;
public:
    Logger() : _queue_index_write(0), _queue_index_read(0) {}
    virtual bool Launch();
    virtual bool Shutdown();

    virtual void LogSyn(char * path, char * log,  char * filename, int line);
    virtual void LogAsyn(char * path, char * log,  char * filename, int line);

    virtual void Run();
private:
    LOGFILE_MAP _logfile_map;

    logunit _queue[ASYN_TEMP_QUEUE_SIZE];
    int _queue_index_write;
    int _queue_index_read;
};

#endif // __FRAMEWORK_LOGGER__