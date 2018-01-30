#ifndef __FRAMEWORK_LOGIC__
#define __FRAMEWORK_LOGIC__

#include <unordered_map>
#include "ILogic.h"

using namespace tcore;

typedef std::unordered_map<const char *, IModule *> MODULE_MAP;
class Logic : public ILogic {
public:
    virtual bool Launch();
    virtual bool Shutdown();

    virtual IModule * FindModule(const char * name);
private:
    MODULE_MAP _module_map;
};
#endif // __FRAMEWORK_LOGIC__
