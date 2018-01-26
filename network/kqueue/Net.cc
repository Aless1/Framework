#include "Net.h"

using namespace tcore;

int g_kqueue = 0;

INet * tcore::GetNetInstance() {
    static INet * s_net = new Net();
    return s_net;
}

bool Net::Init() {
    g_kqueue = kqueue();
    return true;
}

bool Net::Update() {
    struct kevent events[KQUEUE_MAX_EV_COUNT];
    while (true)
    {
        int ret = kevent(g_kqueue, NULL, 0, events, KQUEUE_MAX_EV_COUNT, NULL);
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
    int ret = kevent(g_kqueue, &event, 1, NULL, 0, NULL);
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
    Associat * associat = (Associat *)e.udata;
    int sock = e.ident;

    switch(associat->type) {
    case SO_ACCEPT:
    {
        Accept * ac = associat->ac;
        int count = e.data;
        for(int i = 0; i < count; i++) {
            int client = accept(ac->sock, NULL, NULL);
            Associat * associat = Associat::CreatePipe(client, ac->server->OnMallocSession());
            EV_SET(&e, client, EVFILT_READ, EV_ADD, 0, 0, (void *)associat);
            int ret = kevent(g_kqueue, &e, 1, NULL, 0, NULL);
            if (ret == -1) {
                std::cerr << "kevent register";
            }
            if (e.flags & EV_ERROR) {
                std::cerr << "Event error:" << strerror(e.data);
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
        char data[RECV_TEMP_LEN];
        if(EVFILT_READ == e.filter) {
            int len = recv(sock, data, RECV_TEMP_LEN, 0);
            if(len == 0) {
                p->close();
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
        } else if (EVFILT_WRITE == e.filter) {
            int len = sizeof(data);
            p->send_buff->Read(data, len);
            int ret = send(sock, data, len, 0);
            if(ret == len) {
                EV_SET(&e, sock, EVFILT_WRITE, EV_DISABLE, 0, 0, (void *)associat);
                int ret = kevent(g_kqueue, &e, 1, NULL, 0, NULL);
                if (ret == -1) {
                    std::cerr << "kevent register";
                }
                if (e.flags & EV_ERROR) {
                    std::cerr << "Event error:" << strerror(e.data);
                }
            }
            p->send_buff->Out(ret);
        } else { 
            std::cerr << "unkonw kevent" << e.filter;
        }
        break;
    }
    default:
    {
        break;
    }
    }
}
