#ifndef __FRAMEWORK_ICORE__
#define __FRAMEWORK_ICORE__

#include "INet.h"

namespace tcore {    
class ICore {
public:
    virtual const char * GetParam(const char * name) = 0;
    
    // INet
    virtual bool StartTcpServer(const char * host, int port, ITcpServer * server) = 0;
    virtual bool StartTcpSession(const char * host, int port, ITcpSession * session) = 0;
};

ICore * GetCoreInstance();
}

#endif // __FRAMEWORK_ICORE__
