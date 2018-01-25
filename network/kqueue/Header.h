#ifndef __FRAMEWROK_KQUEUE_HEADER__
#define __FRAMEWROK_KQUEUE_HEADER__

#include <iostream>
#include <sys/event.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "INet.h"
#include "CirBuffer.h"

extern int g_kqueue;

#endif // __FRAMEWROK_KQUEUE_HEADER__
