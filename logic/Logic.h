#ifndef __FRAMEWORK_LOGIC__
#define __FRAMEWORK_LOGIC__

#include <unordered_map>
#include "ILogic.h"
#include "ICore.h"

using namespace tcore;

typedef std::unordered_map<std::string, IModule *> MODULE_MAP;
typedef IModule * GetModule(ICore *);

class Logic : public ILogic {
public:
    virtual bool Launch();
    virtual bool Shutdown();

    virtual IModule * FindModule(const char * name);
private:
    MODULE_MAP _module_map;
};
#endif // __FRAMEWORK_LOGIC__
