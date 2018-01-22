#ifndef __CORE_KQUEUE_HEADER__
#define __CORE_KQUEUE_HEADER__

#include "Accept.h"
#include "Pipe.h"

namespace tcore {

enum {
    SO_ACCEPT,
    SO_CONNECT,
    SO_IO,
};


class Associat {
public:
    static Associat * CreateAccept(const char * ip, int port, ITcpServer * server) {
        int sock = socket(PF_INET, SOCK_STREAM, 0);
        
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip);
        addr.sin_port = htons(port);
        
        if (!(sock = socket(PF_INET, SOCK_STREAM, 0))
            || bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr)) == -1
            || listen(sock, 5) == -1) {
//            std::cerr << "listen() failed:" << errno << std::endl;
//            return -1;
        }
        
        Accept * ac = new Accept(sock, server);
        
        Associat * associat = new Associat();
        associat->type = SO_ACCEPT;
        associat->ac = ac;
        return associat;
    }

    static Associat * CreatePipe(const char * ip, int port, ITcpSession * session) {
        int sock = socket(PF_INET, SOCK_STREAM, 0);
        
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip);
        addr.sin_port = htons(port);
        
        if (!(sock = socket(PF_INET, SOCK_STREAM, 0))
            || bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr)) == -1
            || listen(sock, 5) == -1) {
            //            std::cerr << "listen() failed:" << errno << std::endl;
            //            return -1;
        }
        
        Pipe * pipe = new Pipe(sock, session, 1024, 1024);

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
    ~Associat() {
        if(SO_ACCEPT == type) {
            delete this->ac;
        } else if (SO_CONNECT == type || SO_IO == type) {
            delete this->pipe;
        }
    }
public:
    int type;
    union {
        Accept * ac;
        Pipe * pipe;
    };
};

}

#endif // __CORE_KQUEUE_HEADER__
