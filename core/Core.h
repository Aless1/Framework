#include "ICore.h"
#include "Net.h"
#include "Timer.h"
#include "Logic.h"
#include "Db.h"

#include <unordered_map>>

class Core : public ICore {
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
        if(s_self == NULL) {
            s_self = new Core();;
        }        
        return s_core;
    }

public:
    bool parse(int argc, char * argv[]);
    virtual const char * getParam(const char * name);

private:
    std::unordered_map<const char *, const char *> _param_args;
};
