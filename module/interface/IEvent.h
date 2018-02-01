#ifndef __FRAMEWORK_MODULE_IEVEMT__
#define __FRAMEWORK_MODULE_IEVEMT__

#include "ICore.h"

class IEventHandle {
public: 
    ~IEventHandle() {}
    virtual void PushEvent(void * context, int len) = 0;
};

template<typename T>
class TEventHandle : public IEventHandle {
public:
    typedef void (* Func)(T &t);
    TEventHandle(Func func) : _func(func) {}

    virtual void PushEvent(void * context, int len) {
        if(len != sizeof(T)) {

        }
        _func((T &)context);
    }
private:
    Func _func;
};

template<typename T>
class PEventHandle : public IEventHandle {
public:
    typedef void (* Func)(T * &t);
    PEventHandle(Func func) : _func(func) {}

    virtual void PushEvent(void * context, int len) {
        if(len != sizeof(T *)) {

        }
        _func((T * &)context);
    }
private:
    Func _func;
};

class IEvent : public tcore::IModule {
public:
    virtual bool Init() = 0;
    virtual bool Launch() = 0;
    virtual bool Destory() = 0;
    virtual ~IEvent() {}

    virtual bool Register(int eventid, IEventHandle * event) = 0;
    virtual void PushEvent(int eventid, void * context, int len) = 0;

    template<typename T>
    bool Register(int eventid, void func(T &t)) {
        return Register(eventid, new TEventHandle<T>(func));
    }

    template<typename T>
    bool Register(int eventid, void func(T * &t)) {
        return Register(eventid, new PEventHandle<T>(func));
    }

    template<typename T>
    void PushEvent(int eventid, T &t) {
        PushEvent(eventid, (void *)t, sizeof(T));
    }

    template<typename T>
    void PushEvent(int eventid, T * &t) {
        PushEvent(eventid, (void *)t, sizeof(T *));
    }
};

#endif // __FRAMEWORK_MODULE_IEVEMT__