class ITcpServer;
class ITcpSession;

class IContext {
public:
    IContext(ICore * core) : _core(core) {};

    const char * getParam(char * name);

    bool StartTcpServer(const char * host, const int port, ITcpServer * server);
    bool StartTcpServer(const char * host, const int port, ITcpSession * session);

private:
    ICore * _core;
}
