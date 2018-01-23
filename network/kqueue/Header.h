#ifndef __CORE_KQUEUE_HEADER__
#define __CORE_KQUEUE_HEADER__

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#include "INet.h"
#include "Accept.h"
#include "Pipe.h"

using namespace tcore;

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

#endif // __CORE_KQUEUE_HEADER__
