#include "Core.h"

using namespace tcore;

ICore * tcore::GetCoreInstance() {
    static ICore * s_core = new Core();
    return s_core;
}

const char * Core::GetParam(const char * name) {
    PARAM_ARG_MAP::iterator iter = _param_args.find(name);
    if(iter == _param_args.end()) {
         return NULL;
    }
    return iter->second;
}

bool Core::Parse(int argc, char * argv[]) {
    char key[16];
    for (int i = 1; i < argc; i++) {
        const char * val = strchr(argv[i], '=') + 1;
        if(val) {
            int key_len = val - argv[i] - 1;
            memset(key, 0, sizeof(key));
            memcpy(key, argv[i], key_len);
            _param_args[key] = val;
        }
    }
    return true;
}

bool Core::StartTcpServer(const char * host, int port, ITcpServer * server) {
    return GetNetInstance()->StartTcpServer(host, port, server);
}

bool Core::StartTcpSession(const char * host, int port, ITcpSession * session) {
    return GetNetInstance()->StartTcpSession(host, port, session);
}

IModule * Core::FindModule(const char * name) {
    return GetLogicInstance()->FindModule(name);
}

void Core::LogSyn(const char * log) {
    GetLoggerInstance()->LogSyn(log);

}

void Core::LogAsyn(const char * log) {
    GetLoggerInstance()->LogAsyn(log);
}


IHttpRequest * Core::CreateHttpRequest(int reqid, const char * url, IHttpResponse * response, void * udata = 0) {
    return GetHttpInstance()->CreateHttpRequest(reqid, url, response, udata);
}

bool Core::DoRequest(IHttpRequest * req) {
    return GetHttpInstance()->DoRequest(req);
}