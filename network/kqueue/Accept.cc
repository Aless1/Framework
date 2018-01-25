#include "Accept.h"
#include "Associat.h"

Accept::Accept(Associat * associat, ITcpServer * server, const char * ip, int port) : associat(associat), server(server) {
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

Accept::~Accept() {
    struct kevent e;
    EV_SET(&e, sock, EVFILT_READ, EV_DELETE, 0, 0, NULL);
    int ret = kevent(g_kqueue, &e, 1, NULL, 0, NULL);
    if (ret == - 1) {
        std::cerr << "kevent register";
    }

    ::close(sock);
}

void Accept::close() {
   delete associat;
}

