#ifndef __FRAMEWORK_CORE__
#define __FRAMEWORK_CORE__

#include <unordered_map>

#include "ICore.h"
#include "INet.h"
#include "ILogic.h"
#include "ILogger.h"
#include "IHttp.h"

namespace tcore {
class Core : public ICore {
typedef std::unordered_map<std::string, const char *> PARAM_ARG_MAP;
public:
    virtual const char * GetParam(const char * name);
    
    virtual bool StartTcpServer(const char * host, int port, ITcpServer * server);
    virtual bool StartTcpSession(const char * host, int port, ITcpSession * session);

    virtual IModule * FindModule(const char * name);

    virtual void LogSyn(const char * log);
    virtual void LogAsyn(const char * log);

    virtual IHttpRequest * CreateHttpRequest(int reqid, const char * url, IHttpResponse * response, void * udata);
    virtual bool DoRequest(IHttpRequest * req);
public:
    bool Parse(int argc, char * argv[]);

private:
    PARAM_ARG_MAP _param_args;
};
}

#endif // __FRAMEWORK_ICORE__