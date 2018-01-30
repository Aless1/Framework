#ifndef __FRAMEWORK_ILOGIC__
#define __FRAMEWORK_ILOGIC__

#include "IModule.h"

namespace tcore {
class ILogic {
public:
    virtual bool Launch() = 0;
    virtual bool Shutdown() = 0;

    virtual IModule * FindModule(const char * name) = 0;
};

ILogic * GetLogicInstance();
}

#endif // __FRAMEWORK_ILOGIC__
