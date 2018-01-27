#include "Accept.h"

Accept::Accept(ITcpServer * server, int socket, int recv_size, int send_size) : 
    server(server), sock(socket), recv_size(recv_size), send_size(send_size) {
    associat.type = SO_ACCEPT;
    associat.ac = this;
}

Accept::~Accept() {
    ::close(sock);
}

Accept * Accept::Create(ITcpServer * server, const char * ip, int port, int recv_size, int send_size) {
    int socket = CreateSocket();
    if(INVALID_FD == socket) {
        return NULL;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    if(SOCK_ERROR == bind(socket, (struct sockaddr*)&addr, sizeof(struct sockaddr)) 
        || SOCK_ERROR == listen(socket, 5)) {
        std::cerr << "listen() failed:" << errno << std::endl;
        return NULL;
    }

    return new Accept(server, socket, recv_size, send_size);
}

void Accept::Close() {
    SetEventState(sock, EVFILT_READ, EV_DELETE, NULL);
    delete this;
}