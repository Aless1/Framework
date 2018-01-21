#ifndef __FRAMEWORK_INET__
#define __FRAMEWORK_INET__

#include "ICM.h"

namespace tcore {
class ITcpServer;
class ITcpSession;

class INet : public ICM{
public:
    virtual bool Init() = 0;
    virtual bool Update() = 0;
    virtual bool Destory() = 0;
    
    virtual bool StartTcpServer(const char * host, int port, ITcpServer * server) = 0;
    virtual bool StartTcpSession(const char * host, int port, ITcpSession * session) = 0;
};
    
INet * GetNetInstance();
}
#endif // __FRAMEWORK_INET__
