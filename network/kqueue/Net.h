#ifndef __CORE_KQUEUE_NET_
#define __CORE_KQUEUE_NET_

#include "Header.h"

using namespace tcore;

class Net : public INet {
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
#endif //__CORE_KQUEUE_NET_

