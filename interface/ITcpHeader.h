#ifndef __CORE_ITCPHEADER__
#define __CORE_ITCPHEADER__
namespace tcore {
class ITcpSession;
class IPipe {
public:
    virtual void send(char * data, int len) = 0;
    virtual void close() = 0;

    virtual ~IPipe() {};
};

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
    void Send(char * data, int len) {
        _pipe->send(data, len);
    }
    void Close() {
        _pipe->close();
    }

    void SetPipe(IPipe * pipe) {
        _pipe = pipe;
    }
private:
    IPipe * _pipe;
};
}
#endif // __CORE_ITCPHEADER__
