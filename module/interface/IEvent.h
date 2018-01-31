#ifndef __FRAMEWORK_MODULE_IEVEMT__
#define __FRAMEWORK_MODULE_IEVEMT__

#include "ICore.h"

class IEvent : public tcore::IModule {
public:
    virtual bool Init() = 0;
    virtual bool Launch() = 0;
    virtual bool Destory() = 0;

    template<typename... Args>
    virtual void Register(int eventid, void * func(Args... args)) = 0;
    
    virtual void UnRegister(int eventid) = 0;

    virtual ~IEvent() {}
};

#endif // __FRAMEWORK_MODULE_IEVEMT__