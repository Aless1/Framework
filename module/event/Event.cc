#include "Event.h"
#include <iostream>

using namespace std;

bool Event::Init() {
    cout << "Event Init" << endl;
    return true;
}

bool Event::Launch() {
    cout << "Event Launch" << endl;
    return true;
}

bool Event::Destory() {
    cout << "Event Destory" << endl;
    return true;
}

bool Event::Register(int eventid, IEventHandle * event) {
    EVENT_MAP::iterator iter = _event_map.find(eventid);
    if(iter == _event_map.end()) {
       iter = _event_map.insert(std::pair<int, EVENT_LIST>(eventid, EVENT_LIST())).first;
    }
    iter->second.push_back(event);
    return true;
}

void Event::PushEvent(int eventid, void * context, int len) {
    EVENT_MAP::iterator iter = _event_map.find(eventid);
    if(iter != _event_map.end()) {
        EVENT_LIST::iterator itor = iter->second.begin();
        while(itor != iter->second.end()) {
            (*itor)->PushEvent(context, len);
            itor++;
        }
    }
}