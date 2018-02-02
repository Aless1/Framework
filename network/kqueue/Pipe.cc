#include "Pipe.h"

Pipe * Pipe::Create(ITcpSession * session, const char * ip, int port, int recv_size, int send_size) {
    int socket = CreateSocket();
    if(INVALID_FD == socket) {
        return NULL;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    int ret = connect(socket, (sockaddr *)&addr, sizeof(struct sockaddr));

    if (NO_ERROR == ret) {
        return new Pipe(session, socket, SO_IO, recv_size, send_size);
    } else if (ret < 0 && errno != EINPROGRESS) {
        std::cout << "connect err" << std::endl;
        return NULL;
    } else {
        return new Pipe(session, socket, SO_CONNECT, recv_size, send_size);
    }
}

Pipe * Pipe::Create(ITcpSession * session, int socket, int recv_size, int send_size) {
    if(INVALID_FD == socket) {
        return NULL;
    }
    return new Pipe(session, socket, SO_IO, recv_size, send_size);
}

Pipe::Pipe(ITcpSession * session, int socket, int state, int recv_size, int send_size) : session(session), sock(socket) {
    associat.type = state;
    associat.pipe = this;
    
    session->SetPipe(this);

    recv_buff = new Lib::CirBuffer(recv_size);
    send_buff = new Lib::CirBuffer(send_size);
}

Pipe::~Pipe() {
    ::close(sock);
    delete recv_buff;
    delete send_buff;
}

void Pipe::Send(void * data, int len) {
    if(!SetEventState(sock, EVFILT_WRITE, EV_ADD|EV_ENABLE, (void *)&associat)) {
        Close();
    }

    send_buff->Write(data, len);
}

void Pipe::Close() {
    session->OnDisConnect();

    SetEventState(sock, EVFILT_READ, EV_DELETE, NULL);
    SetEventState(sock, EVFILT_WRITE, EV_DELETE, NULL);

    delete this;
}
