#include "Tools.h"

#include <sys/stat.h>
#include <sys/types.h>

namespace tools {
    bool SafeStrcmp(const char *__restrict __dest, const char *__restrict __src) {
        return !strcmp(__dest, __src);
    }

    void SafeMemcpy(void *__restrict __dest, size_t __max, const void *__restrict __src, size_t __n) {
        tassert(__n <= __max, "over flow");
        memcpy(__dest, __src, (__max >= __n) ? (__n) : (__max));
    }

    void SafeMemset(void *__restrict __dest, size_t __max, int val, size_t __n) {
        tassert(__n <= __max, "over flow");
        memset(__dest, val, (__max >= __n) ? (__n) : (__max));
    }

    int StringAsInt(const char * str) {
        tassert(str, "null point");
        return atoi(str);
    }

    long long StringAsInt64(const char * str) {
        tassert(str, "null point");
        return atoll(str);
    }

    float StringAsFloat(const char * str) {
        tassert(str, "null point");
        return atof(str);
    }

    bool StringAsBool(const char * str) {
        tassert(str, "null point");
        if (!strcmp(str, "true")) {
            return true;
        }
        return false;
    }

    namespace file {
        bool MakeDir(const char * path) {
            return 0 == mkdir(path, S_IRWXU | S_IRWXG);
        }
    }
}