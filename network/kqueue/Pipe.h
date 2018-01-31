#ifndef __KQUEUE_PIPE__
#define __KQUEUE_PIPE__

#include "Header.h"

using namespace tcore;

struct Associat;
class Pipe : public IPipe {
public:
    Pipe(ITcpSession * session, int socket, int state, int recv_size, int send_size);

    virtual ~Pipe();

public:
    static Pipe * Create(ITcpSession * session, const char * ip, int port, int recv_size, int send_size);
    static Pipe * Create(ITcpSession * session, int socket, int recv_size, int send_size);

    virtual void Send(void * data, int len);
    virtual void Close();

public:
    ITcpSession * session;
    int sock;

    struct Associat associat;
    Tools::CirBuffer * recv_buff;
    Tools::CirBuffer * send_buff;
};

#endif // __KQEUEUE_PIPE__