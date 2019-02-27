//
// Created by ben on 19-2-27.
//

#ifndef TCPCLIENT_DEMO6_CLIENTSOCKET_H
#define TCPCLIENT_DEMO6_CLIENTSOCKET_H

#include "common.h"

class ClientSocket
{
private:
    int _socket;

public:

    ClientSocket();

    ~ClientSocket();

    void socket();

    void connect(const char *ip, short port);

    void close();

    bool isAvailable();
};

#endif //TCPCLIENT_DEMO6_CLIENTSOCKET_H
