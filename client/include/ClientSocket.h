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

    void connect(const char *ip, unsigned short port);

    void close();

    bool isAvailable();

    void perrorAndExit(const char *msg);
};

#endif //TCPCLIENT_DEMO6_CLIENTSOCKET_H
