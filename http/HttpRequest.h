#ifndef __CORE_HTTPREQUEST__
#define __CORE_HTTPREQUEST__

#include "IHttp.h"

using namespace tcore;

class HttpRequest : public IHttpRequest {
public:
    HttpRequest(const char * url) {}

    virtual void SetParam(const char * key, const char * value);
    virtual void Post();

    static HttpRequest * Create(const char * url);
private:

};

#endif // __CORE_HTTPREQUEST__