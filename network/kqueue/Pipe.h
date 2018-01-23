#ifndef __KQUEUE_PIPE__
#define __KQUEUE_PIPE__

#include "ICore.h"

namespace tcore {
class Pipe {
public:
    Pipe(int socket, ITcpSession * session, int recv_size, int send_size) : sock(socket), session(session) {
        recv_buff = new Tools::CirBuffer(recv_size);
        send_buff = new Tools::CirBuffer(send_size);
    }
    
    ~Pipe() {
        delete recv_buff;
        delete send_buff;
    }

public:
    Tools::CirBuffer * recv_buff;
    Tools::CirBuffer * send_buff;
    int sock;
    ITcpSession * session;
};
}

#endif // __KQEUEUE_PIPE__
