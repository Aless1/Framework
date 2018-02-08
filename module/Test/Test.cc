#include "Test.h"
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace tcore;

IEvent * g_event = NULL;

class TestSession : public ITcpSession {
public:
    virtual int OnRecv(void * data, int len) {
        std::cout<< "OnRecv" << std::endl;
        return len;
    }
    virtual void OnConnected() {
        int a = 111;
        g_event->PushEvent(1, a);
        std::cout<< "OnConnected" << std::endl;
    }
    virtual void OnDisConnect() {
        std::cout<< "OnDisConnect" << std::endl;
    }
};

class TestServer : public ITcpServer {
public:
    virtual tcore::ITcpSession * OnMallocSession() {
        return new TestSession();
    }
};

class TestResponse : public IHttpResponse {
public:
    virtual void OnResponse(int rid, void * context, int len, void * udata) {
        printf("rid:%d context:%s len:%d udata:%d\n", rid, context, len, udata);
    }
    virtual void OnError(int rid, void * udata) {
        printf("Response OnError");
    }
};

bool Test::Init() {
    return true;
}

bool Test::Launch() {
    // http
    IHttpRequest * requset = GetCoreInstance()->CreateHttpRequest(1, "http://www.baidu.com", new TestResponse(), (void *)1);
    GetCoreInstance()->DoRequest(requset);

    // log
    ERROR_LOG("this is a error log");
    INFO_LOG("this is a info log");

    // tcp
    GetCoreInstance()->StartTcpServer("0.0.0.0", 8089, new TestServer());
    return true;
}

bool Test::Destory() {
    cout << "Test Destory" << endl;
    return true;
}

void Test::TestEvent(int & a) {
    printf("%d\n", a);
}