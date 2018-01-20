#ifndef __CORE_KQUEUE_HEADER__
#define __CORE_KQUEUE_HEADER__

namespace tcore {

class Accept;
class Pipe;

enum EVENT_TYPE {
    
};

class Associat {
public:
    static Associat * CreateAccept(ITcpServer * server) {
        Accept * ac = new Accept();
        ac->server = server;

        Associat * associat = new Associat();
        associat->type = ;
        associat->ac = ac;
    }

    static Associat * CreatePipe(ITcpSession * session) {
        Pipe * pipe = new Pipe();
        pipe->session = session;

        Associat * associat = new Associat();
        associat->type = ;
        associat->pipe = pipe;
    }
private:
    Associat() {}
    ~Associat() {
        if( == type) {

        } else if ( == type) {
            
        }
    }
public:
    int type;
    union {
        Accept * ac;
        Pipe * pipe;
    }   
};

}

#endif // __CORE_KQUEUE_HEADER__
