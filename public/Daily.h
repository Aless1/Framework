#ifndef __TOOLS_DAILY__
#define __TOOLS_DAILY__

#include <sys/time.h>

namespace Tools {
    static long long getCurrentTime() {
        struct timeval tv;      
        gettimeofday(&tv,NULL);    //该函数在sys/time.h头文件中  
        return tv.tv_sec * 1000 + tv.tv_usec / 1000;      
    }
}

#endif // __TOOLS_DAILY__
