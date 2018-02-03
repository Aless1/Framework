#ifndef __FRAMEWORK_HTTP__
#define __FRAMEWORK_HTTP__

#include "IHttp.h"
#include "TQueue.h"
#include "Thread.h"

#define HTTP_THREAD_COUNT 4

#define QUEUE_REQUEST_COUNT 128
#define QUEUE_RESPONSE_COUNT 128

using namespace tcore;
using namespace Lib;

class Http : public IHttp, public Thread {
public:
    virtual ~Http() {}

    virtual bool Launch();
    virtual bool Shutdown();

    virtual IHttpRequest * CreateHttpRequest(int reqid, const char * url, IHttpResponse * response, void * udata);
    virtual bool DoRequest(IHttpRequest * req);

    virtual void Run();

private:
    TQueue<IHttpRequest> _queue_request;
    TQueue<IHttpRequest> _queue_response;
};

#endif // __FRAMEWORK_HTTP__