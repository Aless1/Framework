#ifndef __MODULE_TEST__
#define __MODULE_TEST__

#include "ITest.h"
#include "IEvent.h"

#include <iostream>

class Test : public ITest {
public:
    virtual bool Init();
    virtual bool Launch();
    virtual bool Destory();   

    static void TestEvent(int & a);
};

#endif // __MODULE_TEST__
