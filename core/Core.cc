#include "Core.h"

using namespace tcore;

ICore * tcore::GetCoreInstance() {
    static ICore * s_core = new Core();
    return s_core;
}

const char * Core::GetParam(const char * name) {
    return _param_args[name];
}

bool Core::StartTcpServer(const char * host, int port, ITcpServer * server) {
    return GetNetInstance()->StartTcpServer(host, port, server);
}

bool Core::StartTcpSession(const char * host, int port, ITcpSession * session) {
    return GetNetInstance()->StartTcpSession(host, port, session);
}

bool Parse(int argc, char * argv[]) {
    return true;
}
