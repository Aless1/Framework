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

#define GET_MODULE \
namespace tcore { \
class ICore; \
static ICore * s_core = 0; \
ICore * GetCoreInstance() { \
    return s_core; \
} \
} \
static tcore::IModule * s_module = 0; \
extern "C" tcore::IModule * GetModule(tcore::ICore * core) { \
    tcore::s_core = core; \
    return s_module; \
}

#define ADD_MODULE(module) \
class module##Factory { \
public: \
    module##Factory() { \
        tcore::IModule * m = new module(); \
        m->next = s_module; \
        s_module = m; \
    } \
}; \
module##Factory f;

#endif // __CORE_IMODULE__