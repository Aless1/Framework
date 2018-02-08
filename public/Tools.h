#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "MultSys.h"
#include <string>

using namespace std;

namespace tools {  
    bool SafeStrcmp(const char *__restrict __dest, const char *__restrict __src);
    void SafeMemcpy(void *__restrict __dest, size_t __max, const void *__restrict __src, size_t __n);
    void SafeMemset(void *__restrict __dest, size_t __max, int val, size_t __n);

    int       StringAsInt  (const char * str);
    long long StringAsInt64(const char * str);
    float     StringAsFloat(const char * str);
    bool      StringAsBool (const char * str);

    namespace file {
        bool MakeDir(const char * path);
    }

    int Rand(long long seed, int range);
}

#endif // __TOOLS_H__