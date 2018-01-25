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
        Associat * associat = new Associat();
        Accept * ac = new Accept(associat, server, ip, port);
        associat->type = SO_ACCEPT;
        associat->ac = ac;
        return associat;
    }

    static Associat * CreatePipe(const char * ip, int port, ITcpSession * session) {
        Associat * associat = new Associat();
        Pipe * pipe = new Pipe(associat, session, ip, port, 1024, 1024);
        associat->type = SO_CONNECT;
        associat->pipe = pipe;

        session->SetPipe(pipe);
        
        return associat;
    }

    static Associat * CreatePipe(int socket, ITcpSession * session) {
        Associat * associat = new Associat();
        Pipe * pipe = new Pipe(associat, session, socket, 1024, 1024);
        associat->type = SO_IO;
        associat->pipe = pipe;

        session->SetPipe(pipe);

        return associat;  
    }

    ~Associat() {
        if(SO_ACCEPT == type) {
            delete this->ac;
        } else if (SO_CONNECT == type || SO_IO == type) {
            delete this->pipe;
        }
    }

private:
    Associat() {}

public:
    int type;
    union {
        Accept * ac;
        Pipe * pipe;
    };
};

#endif // __KQUEUE_ASSOCIAT__