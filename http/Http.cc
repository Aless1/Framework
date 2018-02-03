#include "Http.h"
#include "HttpRequest.h"

#include <curl/curl.h>

using namespace tcore;

IHttp * tcore::GetHttpInstance() {
    static IHttp * s_http = new Http();
    return s_http;
}

bool Http::Launch() {
    Start(HTTP_THREAD_COUNT);
    return true;
}

bool Http::Shutdown() {
    return true;
}

IHttpRequest * Http::CreateHttpRequest(int reqid, const char * url, IHttpResponse * response, void * udata) {
    IHttpRequest * req = HttpRequest::Create(url);
    return req;
}

bool Http::DoRequest(IHttpRequest * req) {
    return _queue_request.Push(req);
}

void Http::Run() {
    IHttpRequest * request;
    while(_status != THREAD_STOPING) {
        if(!(request = _queue_request.Pull(false))) {
            sleep(1);
        }
        // IHttpResponse * response = IHttpResponse::Create();
        // _queue_response.Push(response);
    }
    _status = THREAD_STOPED;
}