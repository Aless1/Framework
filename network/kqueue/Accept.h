#ifndef __KQUEUE_ACCEPT__
#define __KQUEUE_ACCEPT__

#include "Header.h"
#include "CirBuffer.h"

class Accept {
public:
    Accept(int socket, ITcpServer * server) : _sock(socket) {}
    ~Accept() {}
public:
    int sock;
    ITcpServer * server;
}

#endif // __KQEUEUE_ACCEPT__
