#include "IContext.h"

public bool IContext::StartTcpServer(const char * host, const int port, ITcpServer * server) {
    return _core->getNetInstancn()->StartTcpServer(host, port, server);
}

public bool IContext::StartTcpSession(const char * host, const int port, ITcpSession * session) {
    return _core->getNetInstancn()->StartTcpSession(host, port, session);
}

public bool IContext::getParam(const char * name) {
    return _core->getParam(name);
}
