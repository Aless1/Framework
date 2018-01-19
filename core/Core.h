#include "ICore.h"
#include "Net.h"
#include "Timer.h"
#include "Logic.h"
#include "Db.h"

#include <unordered_map>>

namespace tcore {
ICore * g_core = NULL;

class Core : public ICore {
public:
    virtual char * getParam(const char * name);
    virtual bool StartTcpServer();
    virtual bool StartTcpSession();

public:
    bool parse(int argc, char * argv[]);


public:
    static Net * getNetInstance() {
        return Net::getInstance();
    }

    static Db * getDbInstance() {
        return Db::getInstance();
    }

    static Timer * getTimerInstance() {
        return Timer::getInstance();
    }
    
    static Logic * getLogicInstance() {
        return Logic::getInstance();
    }

    static getInstance() {
        if(g_core == NULL) {
            g_core = new Core();;
        }        
        return g_core;
    }

private:
    std::unordered_map<const char *, const char *> _param_args;
};
}
