#include "ICore.h"
#include "INet.h"

#include <unordered_map>

using namespace tcore;

class Core : public ICore {
public:
    virtual const char * GetParam(const char * name);
    
    // INet
    virtual bool StartTcpServer(const char * host, int port, ITcpServer * server);
    virtual bool StartTcpSession(const char * host, int port, ITcpSession * session);

public:
    bool Parse(int argc, char * argv[]);

private:
    std::unordered_map<const char *, const char *> _param_args;
};