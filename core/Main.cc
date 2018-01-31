#include "Core.h"
using namespace tcore;

int main(int argc, char * argv[]) {
    ((Core *)GetCoreInstance())->Parse(argc, argv);
    if(!GetNetInstance()->Launch()) {

    }

    if(GetLogicInstance()->Launch()) {

    }
    
    while(1) {
        GetNetInstance()->Proess(5);
    }
    return 0;
}