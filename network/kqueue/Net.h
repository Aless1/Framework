#ifndef __CORE_KQUEUE_NET_
#define __CORE_KQUEUE_NET_

#include "ICM.h"
#include "Header.h"
#include "Accept.h"
#include "Pipe.h"

using namespace tcore;

class Net : public ICM{
public:
    virtual bool init();
    virtual bool update();
    virtual bool destory();
private:
    
};
#endif //__CORE_KQUEUE_NET_

