#include "Test.h"
#include <iostream>

using namespace std;
using namespace tcore;

IEvent * g_event = NULL;

class TestSession : public tcore::ITcpSession {
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

class TestServer : public tcore::ITcpServer {
public:
    virtual tcore::ITcpSession * OnMallocSession() {
        return new TestSession();
    }
};

bool Test::Init() {
    cout << "Test Init" << endl;
    return true;
}

bool Test::Launch() {
    cout << "Test Launch" << endl;
    g_event = (IEvent *)GetCoreInstance()->FindModule("Event");
    g_event->Register(1, TestEvent);
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