#ifndef __KQUEUE_ASSOCIAT__
#define __KQUEUE_ASSOCIAT__

#include "Pipe.h"
#include "Accept.h"

enum {
    SO_ACCEPT,
    SO_CONNECT,
    SO_IO,
};

class Associat {
public:
    static Associat * CreateAccept(const char * ip, int port, ITcpServer * server) {
        Accept * ac = new Accept(ip, port, server);
        
        Associat * associat = new Associat();
        associat->type = SO_ACCEPT;
        associat->ac = ac;
        return associat;
    }

    static Associat * CreatePipe(const char * ip, int port, ITcpSession * session) {
        Pipe * pipe = new Pipe(ip, port, session, 1024, 1024);

        Associat * associat = new Associat();
        associat->type = SO_CONNECT;
        associat->pipe = pipe;
        
        return associat;
    }

    static Associat * CreatePipe(int socket, ITcpSession * session) {
        Pipe * pipe = new Pipe(socket, session, 1024, 1024);
        Associat * associat = new Associat();
        associat->type = SO_IO;
        associat->pipe = pipe;

        return associat;  
    }

private:
    Associat() {}
public:
    ~Associat() {
        if(SO_ACCEPT == type) {
            this->ac->close();
        } else if (SO_CONNECT == type || SO_IO == type) {
            this->pipe->close();
        }
    }
public:
    int type;
    union {
        Accept * ac;
        Pipe * pipe;
    };
};

#endif // __KQUEUE_ASSOCIAT__