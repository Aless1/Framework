#include "Core.h"

using namespace tcore;

int main(int argc, char * argv[]) {
    GetNetInstance()->Init();
    while(1) {
        GetNetInstance()->Proess(5);
    }
    return 0;
}
