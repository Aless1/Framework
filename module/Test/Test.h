#ifndef __MODULE_TEST__
#define __MODULE_TEST__

#include "ITest.h"
#include <iostream>

class TestSession : public tcore::ITcpSession {
public:
    virtual int OnRecv(void * data, int len) {
        std::cout<< "OnRecv" << std::endl;
        return len;
    }
    virtual void OnConnected() {
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

class Test : public ITest {
public:
    virtual bool Init();
    virtual bool Launch();
    virtual bool Destory();   
};

#endif // __MODULE_TEST__
