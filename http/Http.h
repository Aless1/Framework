#ifndef __FRAMEWORK_HTTP__
#define __FRAMEWORK_HTTP__

#include "IHttp.h"
#include "TQueue.h"
#include "Thread.h"
#include "HttpRequest.h"

#define HTTP_THREAD_COUNT 1

#define QUEUE_REQUEST_COUNT 128
#define QUEUE_RESPONSE_COUNT 128

using namespace tcore;
using namespace Lib;

class Http : public IHttp, public Thread {
public:
    virtual ~Http() {}

    virtual bool Launch();
    virtual bool Update();
    virtual bool Shutdown();

    virtual IHttpRequest * CreateHttpRequest(int reqid, const char * url, IHttpResponse * response, void * udata);
    virtual bool DoRequest(IHttpRequest * req);

    virtual void Run();

    static int HttpResponseWrite(char * ptr, int size, int nmemb, void * udata);

private:
    TQueue<HttpRequest> _queue_request;
    TQueue<HttpRequest> _queue_response;
};

#endif // __FRAMEWORK_HTTP__