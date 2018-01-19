#ifndef __FRAMEWORK_CORE__
#define __FRAMEWORK_CORE__

namespace tcore {
class ICore {

public:
    virtual char * getParam(const char * name) = 0;
    virtual bool StartTcpServer() = 0;
    virtual bool StartTcpSession() = 0;
};


extern ICore * g_core;
static IContext * getCore() {
    return g_core;              
}   
}

#endif // __FRAMEWORK_CORE__
