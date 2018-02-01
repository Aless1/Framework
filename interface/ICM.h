#ifndef __FRAMEWROK_ICM__
#define __FRAMEWROK_ICM__

#include "Daily.h"
#include <iostream>

namespace tcore {
class ICM {
public:
    bool Proess(int sec) {
        int res = true;
        long long tick = Tools::GetCurrentTime();
        while(res && Tools::GetCurrentTime() - tick < sec) {
            res &= Update();
        }
        return res;
    }

    virtual bool Launch() = 0;
    virtual bool Update() {
        return true;
    }
    virtual bool Shutdown() = 0;
};
}
#endif // __FRAMEWROK_ICM__