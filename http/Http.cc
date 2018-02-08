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

bool Http::Update() {
    HttpRequest * response;
    if(!(response = _queue_response.Pull(false))) {
        CSLEEP(5);
        return true;
    }
    response->DoResponse();
    return true;
}

IHttpRequest * Http::CreateHttpRequest(int reqid, const char * url, IHttpResponse * response, void * udata) {
    return HttpRequest::Create(reqid, url, response, udata);
}

bool Http::DoRequest(IHttpRequest * req) {
    return _queue_request.Push((HttpRequest *)req);
}

int Http::HttpResponseWrite(char * ptr, int size, int nmemb, void * udata) {
    tools::SafeMemcpy(udata, 10240, ptr, size * nmemb);
    return 0;
}

void Http::Run() {
    CURL * handle = curl_easy_init();
    HttpRequest * request;
    while(_status != THREAD_STOPING) {
        if(!(request = _queue_request.Pull(false))) {
            CSLEEP(50);
            continue;
        }
        curl_easy_reset(handle);
        curl_easy_setopt(handle, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(handle, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(handle, CURLOPT_URL, request->GetUrl());
        curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, HttpResponseWrite);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)request->GetHttpDataCache());

        curl_easy_setopt(handle, CURLOPT_POST, 1);
        // curl_easy_setopt(handle, CURLOPT_POSTFIELDS, request->GetParams());
        int code = curl_easy_perform(handle);
        if (code != CURLE_OK) {
            request->SetError();
        }
        
        _queue_response.Push(request);
        curl_easy_cleanup(handle);
    }
    _thread_count--;
}