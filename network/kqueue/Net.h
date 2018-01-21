#ifndef __CORE_KQUEUE_NET_
#define __CORE_KQUEUE_NET_

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "INet.h"

#include "Header.h"

namespace tcore {

class Net : public INet, public ICM {
public:
    virtual bool Init();
    virtual bool Update();
    virtual bool Destory();
    
    virtual bool StartTcpServer(const char * host, int port, ITcpServer * server);
    virtual bool StartTcpSession(const char * host, int port, ITcpSession * session);
    
private:
    void HandleEvent(struct kevent & e);
    
private:
    int _kq;
};
    
INet * GetNetInstance() {
    static INet * s_net = new Net();
    return s_net;
}
    
}
#endif //__CORE_KQUEUE_NET_

