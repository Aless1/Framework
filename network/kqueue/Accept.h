#ifndef __KQUEUE_ACCEPT__
#define __KQUEUE_ACCEPT__

#include "Header.h"
#include "CirBuffer.h"

using namespace tcore;

class Accept {
public:
    Accept(const char * ip, int port, ITcpServer * server) : server(server) {
        int socket;
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip);
        addr.sin_port = htons(port);
        
        if (!(socket = ::socket(PF_INET, SOCK_STREAM, 0))
            || bind(socket, (struct sockaddr*)&addr, sizeof(struct sockaddr)) == -1
            || listen(socket, 5) == -1) {
            std::cerr << "listen() failed:" << errno << std::endl;
            return;
        }
        sock = socket;
    }
    
    ~Accept() {}
    
public:
    void close();
    //  {
    //     ::close(sock);
    //     delete this;
    // }
    
public:
    int sock;
    ITcpServer * server;
};

#endif // __KQEUEUE_ACCEPT__
