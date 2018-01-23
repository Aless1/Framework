#ifndef __CORE_ICM__
#define __CORE_ICM__

#include "Daily.h"

namespace tcore {
class ICM {
public:
    bool Proess(int sec) {
        int res = true;
        long long tick = Tools::getCurrentTime();
        while(res && Tools::getCurrentTime() - tick < sec) {
            res &= Update();
        }
        return res;
    }

    virtual bool Init() = 0;
    virtual bool Update() = 0;
    virtual bool Destory() = 0;
};
}
#endif // __CORE_ICM__
