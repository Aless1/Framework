#ifndef __FRAMEWORK_CORE__
#define __FRAMEWORK_CORE__
#include "IContext.h""

namespace tcore {
class ICore {
public:
    virtual char * getParam(const char * name) = 0;

    virtual bool StartTcpServer() = 0;
    virtual bool StartTcpSession() = 0;
private:
    static IContext * getContext() {
        static IContext * ctx = new IContext(s_self);
        return ctx;
    }

private:
    static ICore * s_self = NULL;
}
 
static IContext * getContext() {
    return ICore::getContext();              
}   
}

#endif // __FRAMEWORK_CORE__
