#include "Core.h"
using namespace tcore;
#include <string>

int main(int argc, char * argv[]) {
    ((Core *)GetCoreInstance())->Parse(argc, argv);
    if(GetLoggerInstance()->Launch()) {

    }

    if(!GetHttpInstance()->Launch()) {

    }

    if(!GetNetInstance()->Launch()) {

    }

    if(GetLogicInstance()->Launch()) {

    }
    
    while(1) {
        GetNetInstance()->Proess(5);
        GetHttpInstance()->Proess(5);
    }
    return 0;
}