#ifndef __FRAMEWORK_MODULE_EVEMT__
#define __FRAMEWORK_MODULE_EVEMT__

#include "IEvent.h"
#include <iostream>
#include <unordered_map>
#include <list>

typedef std::list<IEventHandle *> EVENT_LIST;
typedef std::unordered_map<int, EVENT_LIST> EVENT_MAP;

class Event : public IEvent {
public:
    virtual bool Init();
    virtual bool Launch();
    virtual bool Destory();

    virtual bool Register(int eventid, IEventHandle * event);
    virtual void PushEvent(int eventid, void * context, int len);

private:
    EVENT_MAP _event_map;
};

#endif // __FRAMEWORK_MODULE_EVEMT__
