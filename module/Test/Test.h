#ifndef __MODULE_TEST__
#define __MODULE_TEST__

#include "ITest.h"

class Test : public tcore::IModule {
public:
    bool Init();
    bool Launch();
    bool Destory();
};

#endif // __MODULE_TEST__
