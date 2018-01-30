#include "Core.h"
using namespace tcore;

int main(int argc, char * argv[]) {
    GetLogicInstance()->Launch();
    GetNetInstance()->Launch();

    // while(1) {
    //     GetNetInstance()->Proess(5);
    // }
    return 0;
}