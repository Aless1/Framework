#ifndef __CORE_KQUEUE_NET_
#define __CORE_KQUEUE_NET_

#include "Pipe.h"
#include "Accept.h"

using namespace tcore;

class Net : public INet {
public:
    virtual bool Launch();
    virtual bool Update();
    virtual bool Shutdown();
    
    virtual bool StartTcpServer(const char * ip, int port, ITcpServer * server, int recv_size, int send_size);
    virtual bool StartTcpSession(const char * ip, int port, ITcpSession * session, int recv_size, int send_size);
    
private:
    void HandleEvent(struct kevent & e);
    
private:
    struct timespec _tick;
};
#endif //__CORE_KQUEUE_NET_

