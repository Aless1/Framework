#include "Net.h"

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int kq = NULL;

public bool Net::init() {
    kq = kqueue();   
    return true;
}

public bool Net::update(int sec) {
    struct kevent events[MAX_EVENT_COUNT];
    while (true)
    {
        int ret = kevent(kq, NULL, 0, events, MAX_EVENT_COUNT, NULL);
        if (ret == -1)
        {
            std::cerr << "kevent failed!\n";
            continue;
        }

        HandleEvent(kq, events, ret);
    }
    return true;
}

public bool Net::destory() {
    return true;
}

public bool Net::StartTcpServer(const char * ip, int port, ITcpServer) {
    int sock = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    if (!(sock = socket(PF_INET, SOCK_STREAM, 0
        || bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr)) == -1
        || listen(sock, 5) == -1) {
        std::cerr << "listen() failed:" << errno << std::endl;
        return -1;
    }

    Accept * ac = new Accept(sock);
    struct event e;
    e.type = EVENT_TYPE.ACCEPT;
    e.ac = ac;

    struct kevent event;
    EV_SET($event, sock, EVFILT_READ, EV_ADD, 0, 0, e);
    ret = kevent(kq, &event, 1, NULL, 0, NULL);
    if (ret == -1)
        std::err << "kevent register";
    if (event.flags & EV_ERROR)
        std::err << "Event error:" << strerror(event.data);
    }
}

private void Net::HandleEvent(struct kevent* events, int nevents) {
    for (int i = 0; i < nevents; i++) {
        int sock = events[i].ident;
        int data = events[i].data;
        struct event  * e = (struct event  *)events[i].udata;

        if (EVENT_TYPE.ACCEPT == event->type) {
            for(int j = 0; j < data; j++) {
            Accept * ac = event->ac;
            int client = accept(ac->socket, NULL, NULL);
            
            Pipe * p = new Pipe(client);
            struct event e;
            e.type = EVENT_TYPE.PIPE;
            e.pipe = p;

            struct kevent event;
            EV_SET($event, client, EVFILT_READ, EV_ADD, 0, 0, e);
            if (ret == -1)
                std::err << "kevent register";
            if (event.flags & EV_ERROR)
                std::err << "Event error:" << strerror(event.data);
            }
        } else if(EVENT_TYPE.PIPE == event->type) {
            Pipe * p = event->pipe;
            int bytes = recv(sock, buf_, availBytes, 0);
        }
    }
}
