#ifndef __CORE_ICORE__
#define __CORE_ICORE__

#include "IModule.h"
#include "ITcpHeader.h"

namespace tcore {

class ICore {
public:
    virtual const char * GetParam(const char * name) = 0;
    
    virtual bool StartTcpServer(const char * host, int port, ITcpServer * server) = 0;
    virtual bool StartTcpSession(const char * host, int port, ITcpSession * session) = 0;

    virtual IModule * FindModule(const char * name) = 0;
};

ICore * GetCoreInstance();
}

#endif // __FRAMEWORK_ICORE__