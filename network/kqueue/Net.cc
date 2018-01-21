#include "Net.h"

using namespace tcore;

#define MAX_EVENT_COUNT 100

bool Net::Init() {
    _kq = kqueue();
    return true;
}

bool Net::Update() {
    struct kevent events[MAX_EVENT_COUNT];
    while (true)
    {
        int ret = kevent(_kq, NULL, 0, events, MAX_EVENT_COUNT, NULL);
        if (ret == -1)
        {
            std::cerr << "kevent failed!\n";
            continue;
        }
        
        for (int i = 0; i < ret; i++) {
            HandleEvent(events[ret]);
        }
    }
    return true;
}

bool Net::Destory() {
    return true;
}

bool Net::StartTcpServer(const char * ip, int port, ITcpServer * server) {
    Associat * associat = Associat::CreateAccept(ip, port, server);
    struct kevent event;
    EV_SET(&event, associat->ac->sock, EVFILT_READ, EV_ADD, 0, 0, (void *)associat);
    int ret = kevent(_kq, &event, 1, NULL, 0, NULL);
//    if (ret == -1)
//        std::err << "kevent register";
//    if (event.flags & EV_ERROR)
//        std::err << "Event error:" << strerror(event.data);
//    }
    return true;
}

bool Net::StartTcpSession(const char * ip, int port, ITcpSession * session) {
    return true;
}

void Net::HandleEvent(struct kevent & e) {
        int sock = e.ident;
        int data = e.data;
        Associat * associat = (Associat *)e.udata;
    
        switch(associat->type) {
        case SO_ACCEPT:
        {
            Accept * ac = associat->ac;
//            for(int k = 0; k < data; k++) {
//                int client = accept(ac->socket, NULL, NULL);
//                Associat * associat = Associat::CreatePipe(ac->server->OnMallocSession());
//                EV_SET($event, client, EVFILT_READ, EV_ADD, 0, 0, associat);
//                int ret = kevent(kq, &event, 1, NULL, 0, NULL);
//                if (ret == -1)
//                    std::err << "kevent register";
//                if (event.flags & EV_ERROR)
//                    std::err << "Event error:" << strerror(event.data);
//                }
//            }
            break;
        }
        case SO_CONNECT:
        {
            break;
        }
                
        case SO_IO:
        {
            Pipe * p = associat->pipe;
            //int bytes = recv(sock, buf_, availBytes, 0);
            break;
        }
        default:
        {
            break;
        }
        }
}
