#ifndef __FRAMEWROK_KQUEUE_HEADER__
#define __FRAMEWROK_KQUEUE_HEADER__

#include <iostream>
#include <sys/event.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <fcntl.h>
#include <netinet/tcp.h>

#include "INet.h"
#include "CirBuffer.h"

#define KQUEUE_MAX_EV_COUNT 512
#define RECV_TEMP_LEN 4096

#define SOCK_ERROR -1
#define NO_ERROR 0

extern int g_kqueue;

static int SetNonblocking(int sockfd) {
    return fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK);
}

static int SetTcpNodelay(const int fd) {
    long val = 1l;
    return setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (const char*)&val, sizeof(val));
}

static int SetReuse(const int fd) {
    long val = 1l;
    return setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&val, sizeof(val));
}

static int SetSockSendBuff(int sock, int size) {
    return setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (const char*)&size, sizeof(size));
}

static int SetSockRecvBuff(int sock, int size) {
    return setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (const char*)&size, sizeof(size));
}

static int SetMaxOpenFile(const int size) {
    struct rlimit rt;
    rt.rlim_max = rt.rlim_cur = size;
    if (setrlimit(RLIMIT_NOFILE, &rt) == -1)
        return -1;
    return 0;
}

static int SetStackSize(const int size) {
    struct rlimit rt;
    rt.rlim_max = rt.rlim_cur = size * 1024;
    if (setrlimit(RLIMIT_STACK, &rt) == -1)
        return -1;
    return 0;
}

#endif // __FRAMEWROK_KQUEUE_HEADER__
