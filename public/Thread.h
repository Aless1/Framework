#ifndef __LIB_THREAD__
#define __LIB_THREAD__

#include <pthread.h>
#include <unistd.h>

namespace Lib {

enum ThradStatus
{   
    THREAD_STARTING,
    THREAD_STARTED,
    THREAD_STOPING,
    THREAD_STOPED
};

class Thread {
public:
    Thread() : _status(THREAD_STARTING) {}
    virtual ~Thread() {}

    virtual void Run() = 0;
    virtual void Terminate();

    void Start(int thread_count);

protected:
    ThradStatus _status;
    int _thread_count;
};
}

#endif // __LIB_THREAD__