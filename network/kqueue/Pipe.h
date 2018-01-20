#ifndef __KQUEUE_PIPE__
#define __KQUEUE_PIPE__

#include "Header.h"

class Pipe {
public:
    Pipe(int socket, ITcpSession * session, recv_size, send_size) : sock(socket), session(session) {
        _recv_buff = new Tools::CirBuffer(recv_size);
        _send_buff = new Tools::CirBuffer(send_size);
    }

public:
    Tools::CirBuffer * recv_buff;
    Tools::CirBuffer * send_buff;
    int sock;
    ITcpSession * session;
}

#endif // __KQEUEUE_PIPE__
