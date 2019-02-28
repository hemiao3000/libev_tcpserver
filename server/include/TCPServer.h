//
// Created by ben on 19-2-27.
//

#ifndef TCPSERVER_DEMO6_TCPSERVER_H
#define TCPSERVER_DEMO6_TCPSERVER_H

#include "ServerSocket.h"
#include "ClientSocket.h"

class ServerSocket;

class ClientSocket;

class TCPServer
{
private:
    ev::default_loop _loop;

    ServerSocket *_serverSocket;

    std::vector<ClientSocket *> *_clientSocketVec;

public:

    TCPServer();

    ~TCPServer();

    void start(const char *ip, unsigned short port);

    void stop();

    bool isRunning();

    void registerClientSocket(ClientSocket *clientSock);

    void unregisterClientSocket(ClientSocket *clientSock);
};

#endif //TCPSERVER_DEMO6_TCPSERVER_H
