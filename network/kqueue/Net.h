#ifndef __CORE_KQUEUE_NET_
#define __CORE_KQUEUE_NET_
#include "ICmd.h"

using namespace tcore;

class Net : public ICmd{
public:
    virtual bool init();
    virtual bool update();
    virtual bool destory();
private:
    
};
#endif //__CORE_KQUEUE_NET_

