#ifndef __FRAMEWORK_IHTTP__
#define __FRAMEWORK_IHTTP__

#include "ICM.h"
#include "IHttpHeader.h"

namespace tcore {
class IHttp : public ICM {
public:
    virtual ~IHttp() {}

    virtual bool Launch() = 0;
    virtual bool Shutdown() = 0;

    virtual IHttpRequest * CreateHttpRequest(int reqid, const char * url, IHttpResponse * response, void * udata = 0) = 0;
    virtual bool DoRequest(IHttpRequest * req) = 0;
};

IHttp * GetHttpInstance();
}

#endif // __FRAMEWORK_IHTTP__