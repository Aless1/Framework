#ifndef __MODULE_TEST__
#define __MODULE_TEST__

#include "ITest.h"

class Test : public ITest {
public:
    virtual bool Init();
    virtual bool Launch();
    virtual bool Destory();   
};

#endif // __MODULE_TEST__
