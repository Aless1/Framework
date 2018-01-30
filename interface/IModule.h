#ifndef __CORE_IMDODLE__
#define __CORE_IMDODLE__

namespace tcore {
class IModule {
public:
    virtual bool Init() = 0;
    virtual bool Launch() = 0;
    virtual bool Destory() = 0;

public:
    IModule * next;
};
}

#define GET_MDOULE \
static tcore::IModule * s_module = NULL; \
extern 'c' static GetMaudle() { \
    return s_module; \
}

#define ADD_MDOULE(module) \
class module##factory { \
    tcore::IModule * m = new module(); \
    m=>next = s_moudle; \
    s_moudle = m; \
} \
module##factory();

#endif // __CORE_IMODULE__
