#ifndef __CORE_ITCPHEADER__
#define __CORE_ITCPHEADER__
namespace tcore {
class ITcpSession;
class IPipe {
public:
    virtual void Send(void * data, int len) = 0;
    virtual void Close() = 0;

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
    void Send(void * data, int len) {
        _pipe->Send(data, len);
    }
    void Close() {
        _pipe->Close();
    }

    void SetPipe(IPipe * pipe) {
        _pipe = pipe;
    }
private:
    IPipe * _pipe;
};
}
#endif // __CORE_ITCPHEADER__
