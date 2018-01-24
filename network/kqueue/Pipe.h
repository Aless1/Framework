#ifndef __KQUEUE_PIPE__
#define __KQUEUE_PIPE__

#include "Header.h"
#include "CirBuffer.h"

using namespace tcore;

class Pipe : public IPipe {
public:
    Pipe(const char * ip, int port, ITcpSession * session, int recv_size, int send_size) : session(session) {
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
        
        recv_buff = new Tools::CirBuffer(recv_size);
        send_buff = new Tools::CirBuffer(send_size);
    }
    
    Pipe(int socket, ITcpSession * session, int recv_size, int send_size) : sock(socket), session(session) {
        recv_buff = new Tools::CirBuffer(recv_size);
        send_buff = new Tools::CirBuffer(send_size);
    }
    
    virtual ~Pipe() {
        delete recv_buff;
        delete send_buff;
    }

public:
    virtual void send(void * data, int len);
    virtual void close();

public:
    Tools::CirBuffer * recv_buff;
    Tools::CirBuffer * send_buff;
    int sock;
    ITcpSession * session;
};

#endif // __KQEUEUE_PIPE__
