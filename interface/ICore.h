#ifndef __CORE_ICORE__
#define __CORE_ICORE__

#include "IModule.h"
#include "ITcpHeader.h"
#include "IHttpHeader.h"

namespace tcore {

class ICore {
public:
    virtual const char * GetParam(const char * name) = 0;
    
    virtual bool StartTcpServer(const char * host, int port, ITcpServer * server) = 0;
    virtual bool StartTcpSession(const char * host, int port, ITcpSession * session) = 0;

    virtual IModule * FindModule(const char * name) = 0;

    virtual void LogSyn(char * path, char * log,  char * filename, int line) = 0;
    virtual void LogAsyn(char * path, char * log,  char * filename, int line) = 0;
};

ICore * GetCoreInstance();
}

#define ERROR_LOG(log) GetCoreInstance()->LogSyn("error", log, __FILE__, __LINE__);
#endif // __FRAMEWORK_ICORE__