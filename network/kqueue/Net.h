#ifndef __CORE_KQUEUE_NET_
#define __CORE_KQUEUE_NET_
#include "ICmd.h"
#include "Accept.h"
#include "Pipe.h"

using namespace tcore;

enum EVENT_TYPE {
    PIPE,
    ACCEPT,
}

struct event {
    int type;
    union {
        Accept * ac;
        Pipe * pipe;
    }
};

class Net : public ICmd{
public:
    virtual bool init();
    virtual bool update();
    virtual bool destory();
private:
    
};
#endif //__CORE_KQUEUE_NET_

