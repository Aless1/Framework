#include "Core.h"

int main(int argc, char * argv[]) {
    if(Core::getInstance()->parse(int argc, char * argv[])) {
        return -1;
    }   

    INet * g_net = Core::getNetInstance();
    ITimer * g_timer = Core::getTimerInstance();
    ILogic * g_logic = Core::getLogicInstacne();
    IDb * g_db = Core::getDbInstance();

    if (!g_net->init() || !g_timer->init() || !g_logic->init() || !g_db->init()) {
        return -1;
    }

    g_logic->exec();

    while(true) {
        g_net->proess(5);
        g_timer->poress(5);
        g_db->proess(5);
    }

    g_logic->destory();
    return 0;
}
