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

    virtual bool Register(int eventid, IEventHandle * event) {
        EVENT_MAP::iterator iter = _event_map.find(eventid);
        if(iter == _event_map.end()) {
           iter = _event_map.insert(std::pair<int, EVENT_LIST>(eventid, EVENT_LIST())).first;
        }
        iter->second.push_back(event);
        return true;
    }

    virtual void PushEvent(int eventid, void * context, int len) {
        EVENT_MAP::iterator iter = _event_map.find(eventid);
        if(iter != _event_map.end()) {
            EVENT_LIST::iterator itor = iter->second.begin();
            while(itor != iter->second.end()) {
                (*itor)->PushEvent(context, len);
                itor++;
            }
        }
    }

private:
    EVENT_MAP _event_map;
};

#endif // __FRAMEWORK_MODULE_EVEMT__
