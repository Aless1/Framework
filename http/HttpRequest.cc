
#include "HttpRequest.h"

using namespace tcore;

HttpRequest * HttpRequest::Create(int id, const char * url, IHttpResponse * response, void * udata) {
   return new HttpRequest(id, url, response, udata);
}

void HttpRequest::Relaase() {
    delete this;
}

const char * HttpRequest::GetUrl() {
    return _url;
}

const char * HttpRequest::GetParams() {
    return "";
}

void * HttpRequest::GetHttpDataCache() {
    return _data;
}

void HttpRequest::SetParam(const char * key, const char * value) {

}

void HttpRequest::Post() {
    GetHttpInstance()->DoRequest(this);
}

void HttpRequest::SetError() {
    
}

void HttpRequest::DoResponse() {
    _response->OnResponse(_id, (void *)_data, strlen(_data), _udate);
    Relaase();
}