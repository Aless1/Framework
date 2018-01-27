#ifndef __FRAMEWORK_INET__
#define __FRAMEWORK_INET__

#include "ICM.h"
#include "ITcpHeader.h"

namespace tcore {

class INet : public ICM {
public:
    virtual bool Init() = 0;
    virtual bool Update() = 0;
    virtual bool Destory() = 0;
    
    virtual bool StartTcpServer(const char * ip, int port, ITcpServer * server, int recv_size = 1024, int send_size = 1024) = 0;
    virtual bool StartTcpSession(const char * ip, int port, ITcpSession * session, int recv_size = 1024, int send_size = 1024) = 0;
};
    
INet * GetNetInstance();
}
#endif // __FRAMEWORK_INET__
