#ifndef __CORE_ICM__
#define __CORE_ICM__
namespace tcore {
class ICM {
public:
    bool proess(int sec) {
        int res = true
        int64 tick = Tools::getCurrentTime();
        while(Tools::getCurrentTime() - tick > sec) {
            res &= update();
        }
        return res;
    }

    virtual bool init() = 0;
    virtual bool update() = 0;
    virtual bool destory() = 0; 
};
}
#endif // __CORE_ICM__
