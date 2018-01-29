#ifndef __MODULE_ITEST__
#define __MODULE_ITEST__

#include "IModule.h"

class Test : public tcore::IModule {
pubic:
    bool Init() = 0;
    bool Launch() = 0;
    bool Destory() = 0;   
};
#endif // __MOUDLE_ITEST__
