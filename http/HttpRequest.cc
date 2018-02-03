#include "HttpRequest.h"

using namespace tcore;

HttpRequest * HttpRequest::Create(const char * url) {
    return new HttpRequest(url);
}

void HttpRequest::SetParam(const char * key, const char * value) {

}

void HttpRequest::Post() {
    GetHttpInstance()->DoRequest(this);
}