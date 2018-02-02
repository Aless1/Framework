#ifndef __LIB_THREAD__
#define __LIB_THREAD__

#include <pthread.h>

namespace Lib {
class Thread {
public:
    virtual ~Thread() {}

    virtual void Run() = 0;
    virtual void Terminate() = 0;

    void Start() {};  
};
}

#endif // __LIB_THREAD__


