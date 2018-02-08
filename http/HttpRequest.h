#ifndef __CORE_HTTPREQUEST__
#define __CORE_HTTPREQUEST__

#include "IHttp.h"
#include "Tools.h"

#define URL_SIZE_MAX 1024

using namespace tcore;

class HttpRequest : public IHttpRequest {
protected:
    HttpRequest(const int id, const char * url, IHttpResponse * response, void * udata) :
    _id(id), _response(response), _udate(udata) {
        tools::SafeMemcpy(_url, URL_SIZE_MAX, url, strlen(url) + 1);
    }

public:
    static HttpRequest * Create(int id, const char * url, IHttpResponse * response, void * udata);
    void Relaase();

    virtual const char * GetUrl();
    virtual const char * GetParams();

    virtual void SetParam(const char * key, const char * value);
    virtual void Post();

    void SetError();
    void * GetHttpDataCache();

    void DoResponse();

private:
    int _id;
    char _url[URL_SIZE_MAX];
    IHttpResponse * _response;
    void * _udate;
    char _data[10240];
};

#endif // __CORE_HTTPREQUEST__