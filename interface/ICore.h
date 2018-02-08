#ifndef __CORE_ICORE__
#define __CORE_ICORE__

#include "IModule.h"
#include "ITcpHeader.h"
#include "IHttpHeader.h"

#include "MultSys.h"

namespace tcore {

class ICore {
public:
    virtual const char * GetParam(const char * name) = 0;
    
    virtual bool StartTcpServer(const char * host, int port, ITcpServer * server) = 0;
    virtual bool StartTcpSession(const char * host, int port, ITcpSession * session) = 0;

    virtual IModule * FindModule(const char * name) = 0;

    virtual void LogSyn(const char * log) = 0;
    virtual void LogAsyn(const char * log) = 0;

    template<typename... Args>
    void LogAsyn(const char * format, Args ...args) {

    }
};

ICore * GetCoreInstance();
}

#define ERROR_LOG(format, ...) \
{ char log[4096]; \
SafeSprintf(log, 4096, "[error] %s:%d:%s : "#format,  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
GetCoreInstance()->LogSyn(log); }

#define INFO_LOG(format, ...) \
{ char log[4096]; \
tools::SafeSprintf(log, 4096, "[info]  %s:%d:%s : "#format,  __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
GetCoreInstance()->LogAsyn(log); }

#endif // __CORE_ICORE__