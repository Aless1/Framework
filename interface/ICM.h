#ifndef __CORE_ICM__
#define __CORE_ICM__

namespace tcore {
class ICM {
public:
    bool Proess(int sec) {
        int res = true;
        //int64 tick = Tools::getCurrentTime();
        //while(Tools::getCurrentTime() - tick > sec) {
        res &= Update();
        //}
        return res;
    }

    virtual bool Init() = 0;
    virtual bool Update() = 0;
    virtual bool Destory() = 0;
};
}
#endif // __CORE_ICM__
