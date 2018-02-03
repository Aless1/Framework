#ifndef __CORE_IHTTPHEADER__
#define __CORE_IHTTPHEADER__

namespace tcore {
class IHttpRequest {
public:
    virtual ~IHttpRequest() {}
    virtual void SetParam(const char * key, const char * value) = 0;
    virtual void Post() = 0;
};

class IHttpResponse {
public:
    virtual ~IHttpResponse() {}

    virtual void OnResponse(int rid, void * context, int len, void * udata) = 0;
    virtual void OnError(int rid, void * udata) = 0;
};
}

#endif // __CORE_IHTTPHEADER__