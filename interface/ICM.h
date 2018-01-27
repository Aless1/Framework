#ifndef __FRAMEWROK_ICM__
#define __FRAMEWROK_ICM__

#include "Daily.h"
#include <iostream>

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
#endif // __FRAMEWROK_ICM__
