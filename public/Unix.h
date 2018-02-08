#ifndef __UNIX_H__
#define __UNIX_H__

#include <unistd.h>

#define SafeSprintf snprintf
#define CSLEEP(n) usleep(n * 1000)

#endif // __UNIX_H__