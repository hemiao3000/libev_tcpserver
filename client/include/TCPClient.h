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
    ClientSocket *_socket;
    ev::timer _timer;
    ev::default_loop _loop;
public:
    TCPClient() {
        _socket = new ClientSocket();
    }

    ~TCPClient() {
        delete _socket;
    }

    void start(const char *ip, unsigned short port);

    void stop();
    

    void TimeOutCallBack(ev::timer &timer, int revents);
};

#endif //TCPCLIENT_DEMO6_TCPCLIENT_H
