#ifndef __MODULE_ITEST__
#define __MODULE_ITEST__

#include "ICore.h"

class ITest : public tcore::IModule {
public:
    virtual bool Init() = 0;
    virtual bool Launch() = 0;
    virtual bool Destory() = 0;

    virtual ~ITest() {}
};

#endif // __MOUDLE_ITEST__