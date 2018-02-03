#include "Thread.h"

using namespace Lib;

static void * ThreadFunc(void * param) {
    Thread * thread = (Thread *)param;
    thread->Run();
    return thread;
}

void Thread::Terminate() {
    if(THREAD_STARTING == _status) {

    }

    if(THREAD_STARTED == _status) {
        _status = THREAD_STOPING;
        while(THREAD_STOPED != _status) {
            sleep(1);
        }
    }
}

void Thread::Start(int thread_count) {
    int err;
    pthread_t pid;
    _status = THREAD_STARTED;
    for (int i = 0; i < thread_count; i++) {
        err = pthread_create(&pid, NULL, ThreadFunc, this);
        if (err != 0) {
            // TODO
        }
    }
}