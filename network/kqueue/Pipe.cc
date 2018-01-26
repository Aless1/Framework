#include "Pipe.h"
#include "Associat.h"

Pipe::Pipe(Associat * associat, ITcpSession * session, const char * ip, int port, int recv_size, int send_size) : associat(associat), session(session) {
    int socket;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    
    if (!(socket = ::socket(PF_INET, SOCK_STREAM, 0))
        || SOCK_ERROR == SetReuse(socket)
        || SOCK_ERROR == SetTcpNodelay(socket)
        || SOCK_ERROR == SetNonblocking(socket)) {
        std::cerr << "listen() failed:" << errno << std::endl;
        return;
    }
    sock = socket;
    
    int ret = connect(socket, (sockaddr *)&addr, sizeof(struct sockaddr));
    
    if (NO_ERROR == ret) {
        std::cout << "connect success" << std::endl;
    } else if (ret < 0 && errno != EINPROGRESS) {
        std::cerr << "connect err" << std::endl;
        return;
    } else {
        std::cout << "connect delay" << std::endl;
        associat->type = SO_CONNECT;
    }
    
    recv_buff = new Tools::CirBuffer(recv_size);
    send_buff = new Tools::CirBuffer(send_size);
}

Pipe::Pipe(Associat * associat, ITcpSession * session, int socket, int recv_size, int send_size) : associat(associat), session(session), sock(socket) {
    recv_buff = new Tools::CirBuffer(recv_size);
    send_buff = new Tools::CirBuffer(send_size);
}

Pipe::~Pipe() {
    struct kevent events[2];
    EV_SET(&events[0], sock, EVFILT_READ, EV_DELETE, 0, 0, NULL);
    EV_SET(&events[1], sock, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
    int ret = kevent(g_kqueue, events, 2, NULL, 0, NULL);
    if (ret == - 1) {
        std::cerr << "kevent register";
    }

    ::close(sock);

    delete recv_buff;
    delete send_buff;
}

void Pipe::send(char * data, int len) {
    struct kevent event;
    EV_SET(&event, sock, EVFILT_WRITE, EV_ADD|EV_ENABLE, 0, 0, (void *)associat);
    int ret = kevent(g_kqueue, &event, 1, NULL, 0, NULL);
    if (ret == -1) {
        std::cerr << "kevent register";
    }
    if (event.flags & EV_ERROR) {
        std::cerr << "Event error:" << strerror(event.data);
    }
    send_buff->Write(data, len);
}

void Pipe::close() {
    session->OnDisConnect();
    delete associat;
}
