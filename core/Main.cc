#include "Core.h"
#include <iostream>

using namespace tcore;

class TestSession : public ITcpSession {
public:
    virtual int OnRecv(void * data, int len) {
        char str[100];
        memset(str, 0, 100);
        memcpy(str, data, len);
        std::cout << str << std::endl;

        Send(str, len);
        return len;
    }
    virtual void OnConnected() {
        std::cout << "OnConnected" << std::endl;
        char * str = "hhhhh\n";
        Send(str, 6);
    }
    virtual void OnDisConnect() {
        std::cout << "OnDisConnect" << std::endl;
        char * str = "bbbbb\n";
    }
};

class TestServer : public ITcpServer {
public:
    virtual ITcpSession * OnMallocSession() {
        ITcpSession * s = new TestSession();
        return s;
    }
};

int main(int argc, char * argv[]) {
    GetNetInstance()->Init();
    GetCoreInstance()->StartTcpServer("0.0.0.0", 8088, new TestServer());
    
    while(1) {
        GetNetInstance()->Proess(5);
    }
    return 0;
}