#ifndef __FRAMEWORK_MODULE_EVEMT__
#define __FRAMEWORK_MODULE_EVEMT__

#include "IEvent.h"
#include <iostream>
#include <unordered_map>

class IEventHandle {
public:
    template<typename... Args>
    virtual void CallBack(Args... args) = 0;
};

template<typename... Args>
class TEventHandle : public IEventHandle {
public:
    typedef void * Func(Args... args);

    TEventHandle(Func func) : _func(func) {}
    virtual void CallBack(Args... args) {
        _func(args...);
    }

private:
    Func _func;
};

typedef std::unordered_map<int, IEvent *> EVENT_MAP;

class Event : public IEvent {
public:
    virtual bool Init();
    virtual bool Launch();
    virtual bool Destory();   


    template<typename... Args>
    virtual void Register(int eventid, void * func(Args... args)) {
        IEventHandle * event = new TEventHandle<args...>(func);
        EVENT_MAP::iterator iter = _event_map.find(eventid);
        if(iter != _event_map.end()) {}
        _event_map[eventid] = event;
    }

    virtual void UnRegister(int eventid) {
        EVENT_MAP::iterator iter = _event_map.find(eventid);
        if(iter != _event_map.end()) {
            _event_map.erase(iter);
        }
    }

private:
    EVENT_MAP _event_map;
};

#endif // __FRAMEWORK_MODULE_EVEMT__
