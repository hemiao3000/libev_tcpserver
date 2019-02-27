//
// Created by ben on 19-2-27.
//

#ifndef TCPCLIENT_DEMO6_TCPCLIENT_H
#define TCPCLIENT_DEMO6_TCPCLIENT_H

#include <ev++.h>
#include "ClientSocket.h"

class TCPClient
{
private:
    ClientSocket _socket;
    ev::timer _timer;
    ev::default_loop _loop;
public:
    TCPClient() = default;

    ~TCPClient() = default;

    void start(const char *ip, short port);

    void TimeOutCallBack(ev::timer &timer, int revents);
};

#endif //TCPCLIENT_DEMO6_TCPCLIENT_H
