#ifndef __TOOLS_DAILY__
#define __TOOLS_DAILY__

#include <sys/time.h>
#include <stdio.h>

namespace Tools {
    static char date[64];

    static long long GetCurrentTime() {
        struct timeval tv;      
        gettimeofday(&tv,NULL);
        return tv.tv_sec * 1000 + tv.tv_usec / 1000;      
    }

    static const char * GetTimeString(const char * format = "%d-%d-%d %d:%d:%d") {        
        time_t timep;
        struct tm * p;
        time(&timep);
        p = localtime(&timep);
        sprintf(date, format, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
        return date;
    }
}

#endif // __TOOLS_DAILY__