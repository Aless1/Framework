#ifndef __MULTSYS_H__
#define __MULTSYS_H__

#include "Unix.h"

void _AssertionFail(const char * file, const char line, const char * func, const char * debug);

#define tassert(p, format, ...) { \
    char debug[4096]; \
    ((p)?void(0):(void)_AssertionFail(__FILE__, __LINE__, __FUNCTION__, debug)); \
}

#endif // __MULTSYS_H__