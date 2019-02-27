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

    // TODO: 添加一个数组/容器，用以记录已建立连接的客户端 socket
    std::vector<ClientSocket *> *_clientSocketVec;

public:

    TCPServer();

    ~TCPServer();

    void start(const char *ip, short port);

    void stop();

    bool isRunning();

    void addClientSocket(ClientSocket *clientSock);

    void removeClientSocket(ClientSocket *clientSock);
};

#endif //TCPSERVER_DEMO6_TCPSERVER_H
