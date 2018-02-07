#include "MultSys.h"

#include <assert.h>
#include <stdio.h>

void _AssertionFail(const char * file, const char line, const char * func, const char * debug) {
    fflush(stdout);
    printf("assert %s:%d : %s\n", file, line, debug);
    fflush(stderr);
    assert(false);
}