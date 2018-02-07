#ifndef __LIB_TQUEUE__
#define __LIB_TQUEUE__

#include <unistd.h>

namespace Lib {
template <typename T, int size = 128>
class TQueue {
public:
    TQueue() : _index_front(0), _index_back(0) {}

    T * Pull(bool block = true) {
        if(block) {
            while (true) {
                if(_index_front == _index_back) {
                    sleep(1); // TODO
                }
                return _queue[_index_front++];
            }
        } else {
            if(_index_front == _index_back) {
                return NULL;
            }
            return _queue[_index_front++];
        }
    }

    bool Push(T * t) {
        int next_index = (_index_back + 1) % size;
        if(_index_front == next_index) {
            return false;
        }
        _queue[_index_back] = t;
        _index_back = next_index;
        return true;
    }
private:
    T * _queue[size];
    int _index_front;
    int _index_back;
};
}

#endif // __LIB_TQUEUE__
