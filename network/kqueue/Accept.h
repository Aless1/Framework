#ifndef __KQUEUE_ACCEPT__
#define __KQUEUE_ACCEPT__

#include "Header.h"

using namespace tcore;

class Accept {
public:
    Accept(ITcpServer * server, int socket, int recv_size, int send_size);
    ~Accept();
public:
    static Accept * Create(ITcpServer * server, const char * ip, int port, int recv_size, int send_size);
    void Close();
    
public:
    int sock;

    int recv_size;
    int send_size;

    struct Associat associat;
    ITcpServer * server;
};

#endif // __KQEUEUE_ACCEPT__
