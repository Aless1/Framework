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
    int ret = kevent(g_kqueue, NULL, 0, events, KQUEUE_MAX_EV_COUNT, NULL);
    if (ret == -1)
    {
        std::cerr << "kevent failed!\n";
        return false;
    }
    for (int i = 0; i < ret; i++) {
        HandleEvent(events[i]);
    }
    return true;
}

bool Net::Destory() {
    return true;
}

bool Net::StartTcpServer(const char * ip, int port, ITcpServer * server, int recv_size, int send_size) {
    Accept * ac = Accept::Create(server, ip, port, recv_size, send_size);
    if(!ac) {
        return false;
    }

    if (!SetEventState(ac->sock, EVFILT_READ, EV_ADD, (void *)&ac->associat)) {
        ac->Close();
        return false;
    }

    return true;
}

bool Net::StartTcpSession(const char * ip, int port, ITcpSession * session, int recv_size, int send_size) {
    Pipe * p = Pipe::Create(session, ip, port, recv_size, send_size);

    if(SO_CONNECT == p->associat.type) {
        if (!SetEventState(p->sock, EVFILT_WRITE, EV_ADD, (void *)&p->associat)) {
            p->Close();
            return false;
        } 
    } else if(SO_IO == p->associat.type) {
        if (!SetEventState(p->sock, EVFILT_READ, EV_ADD, (void *)&p->associat)) {
            p->Close();
            return false;
        }
    }
    return true;
}

void Net::HandleEvent(struct kevent & e) {
    struct Associat * associat = (Associat *)e.udata;
    int sock = e.ident;

    switch(associat->type) {
    case SO_ACCEPT:
    {
        Accept * ac = associat->ac;
        int count = e.data;
        for(int i = 0; i < count; i++) {
            int client = accept(ac->sock, NULL, NULL);

            Pipe * p = Pipe::Create(ac->server->OnMallocSession(), client, ac->recv_size, ac->send_size);
            if (!SetEventState(p->sock, EVFILT_READ, EV_ADD, (void *)&p->associat)) {
                p->Close();
                return;
            }
            p->session->OnConnected();
        }
        break;
    }
    case SO_CONNECT:
    {               
        Pipe * p = associat->pipe;
        associat->type = SO_IO;
        SetEventState(p->sock, EVFILT_READ, EV_ADD, (void *)&p->associat);
        SetEventState(p->sock, EVFILT_READ, EV_ADD, (void *)&p->associat);
        break;
    }                
    case SO_IO:
    {
        Pipe * p = associat->pipe;
        char temp[RECV_TEMP_LEN];
        if(EVFILT_READ == e.filter) {
            int len = recv(sock, temp, RECV_TEMP_LEN, 0);
            if(len == 0) {
                p->Close();
                return;
            }

            p->recv_buff->Write(temp, len);
            p->recv_buff->Read(temp, len);

            int use = 0;
            char * point = temp;
            do {
                use = p->session->OnRecv(point, len);
                p->recv_buff->Out(use);

                point = point + use;
                len = len - use;
            } while (use > 0 && len > 0);

        } else if (EVFILT_WRITE == e.filter) {
            int len = RECV_TEMP_LEN;
            p->send_buff->Read(temp, len);
            int ret = send(sock, temp, len, 0);
            if(ret == len) {
                if (!SetEventState(p->sock, EVFILT_WRITE, EV_DISABLE, (void *)&p->associat)) {
                    p->Close();
                    return;
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
