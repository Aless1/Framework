#ifndef __KQUEUE_ACCEPT__
#define __KQUEUE_ACCEPT__

#include "Header.h"

using namespace tcore;

class Associat;
class Accept {
public:
    Accept(Associat * associat, ITcpServer * server, const char * ip, int port);
    ~Accept();

    void close();
public:
    int sock;

    Associat * associat;
    ITcpServer * server;
};

#endif // __KQEUEUE_ACCEPT__
