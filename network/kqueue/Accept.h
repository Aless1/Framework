#ifndef __KQUEUE_ACCEPT__
#define __KQUEUE_ACCEPT__

#include "CirBuffer.h"
#include "ICore.h"

namespace tcore {
class Accept {
public:
    Accept(int socket, ITcpServer * server) : sock(socket), server(server) {}
    ~Accept() {}
public:
    int sock;
    ITcpServer * server;
};
}

#endif // __KQEUEUE_ACCEPT__
