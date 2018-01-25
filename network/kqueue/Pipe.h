#ifndef __KQUEUE_PIPE__
#define __KQUEUE_PIPE__

#include "Header.h"

using namespace tcore;

class Associat;
class Pipe : public IPipe {
public:
    Pipe(Associat * associat, ITcpSession * session, const char * ip, int port, int recv_size, int send_size);
    Pipe(Associat * associat, ITcpSession * session, int socket, int recv_size, int send_size);

    virtual ~Pipe();

public:
    virtual void send(char * data, int len);
    virtual void close();

public:
    Tools::CirBuffer * recv_buff;
    Tools::CirBuffer * send_buff;
    int sock;

    Associat * associat;
    ITcpSession * session;
};

#endif // __KQEUEUE_PIPE__