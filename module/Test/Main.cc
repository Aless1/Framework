#include "Test.h"

using namespace tcore;
//GET_MDOULE
//ADD_MDOULE(Test)

static tcore::IModule * s_module = 0;
extern "C" tcore::IModule * GetMaudle() {
    return s_module;
}

class TestFactoy {
public:
    TestFactoy() {
        tcore::IModule * m = new Test();
        m->next = s_module;
        s_module = m;
    }
};

TestFactoy testFactoy;