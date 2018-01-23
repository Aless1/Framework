#include "Net.h"

using namespace tcore;

#define MAX_EVENT_COUNT 100

INet * tcore::GetNetInstance() {
    static INet * s_net = new Net();
    return s_net;
}

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
            HandleEvent(events[i]);
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
    if (ret == -1) {
        std::cout << "kevent register";
    }
    if (event.flags & EV_ERROR) {
        std::cout << "Event error:" << strerror(event.data);
    }
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
            for(int i = 0; i < data; i++) {
                int client = accept(ac->sock, NULL, NULL);
                Associat * associat = Associat::CreatePipe(client, ac->server->OnMallocSession());
                struct kevent event;
                EV_SET(&event, client, EVFILT_READ, EV_ADD, 0, 0, (void *)associat);
                int ret = kevent(_kq, &event, 1, NULL, 0, NULL);
                if (ret == -1) {
                    std::cerr << "kevent register";
                }
                if (event.flags & EV_ERROR) {
                    std::cerr << "Event error:" << strerror(event.data);
                }
                associat->pipe->session->OnConnected();
            }
            break;
        }
        case SO_CONNECT:
        {               
            break;
        }                
        case SO_IO:
        {
            Pipe * p = associat->pipe;
            char data[1024];
            int len = recv(sock, data, sizeof(data), 0);
            if(len == 0) {
                p->session->OnDisConnect();
                EV_SET(&e, sock, EVFILT_READ, EV_DELETE, 0, 0, NULL);
                delete associat;
                return;
            }

            p->recv_buff->Write(data, len);
            p->recv_buff->Read(data, len);

            int use = 0;
            char * point = data;
            do {
                use = p->session->OnRecv(point, len);
                p->recv_buff->Out(use);

                point = point + use;
                len = len - use;
            } while (use > 0 && len > 0);
            break;
        }
        default:
        {
            break;
        }
        }
}
