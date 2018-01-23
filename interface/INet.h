#ifndef __FRAMEWORK_INET__
#define __FRAMEWORK_INET__

#include "ICM.h"

namespace tcore {
    class IPipe {
    public:
        virtual void send(void * data, int len) = 0;
        virtual void close() = 0;
    };
    
    class ITcpSession;
    
    class ITcpServer {
    public:
        virtual ITcpSession * OnMallocSession() = 0;
    };
    
    class ITcpSession {
    public:
        virtual int OnRecv(void * data, int len) = 0;
        virtual void OnConnected() = 0;
        virtual void OnDisConnect() = 0;
        
    public:
        void Send(void * data, int len) {
            _pipe->send(data, len);
        }
        void Close() {
            _pipe->close();
        }
    private:
        IPipe * _pipe;
    };

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
