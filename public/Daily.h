#ifndef __UTIL_DAILY__
#define __UTIL_DAILY__

#include <sys/time.h>
#include <stdio.h>

namespace Util {
namespace Daily {
    static char date[64];

    static long long GetCurrentTime() {
        struct timeval tv;      
        gettimeofday(&tv,NULL);
        return tv.tv_sec * 1000 + tv.tv_usec / 1000;      
    }

    static const char * GetTimeString(const long long tick, const char * format = "%d-%d-%d %d:%d:%d") {        
        time_t timep = (time_t)tick;
        struct tm * p;
        time(&timep);
        p = localtime(&timep);
        sprintf(date, format, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
        return date;
    }

    static const char * GetCurrentTimeString(const char * format = "%d-%d-%d %d:%d:%d") {        
        time_t timep;
        struct tm * p;
        time(&timep);
        p = localtime(&timep);
        sprintf(date, format, 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
        return date;
    }
}
}

#endif // __UTIL_DAILY__