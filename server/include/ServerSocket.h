//
// Created by ben on 19-2-27.
//

#ifndef TCPSERVER_DEMO6_SERVERSOCKET_H
#define TCPSERVER_DEMO6_SERVERSOCKET_H

#include <vector>
#include <ev++.h>
#include "common.h"
#include "ClientSocket.h"
#include "TCPServer.h"

/**
 * 将原生的 BSD Socket 及其相关操作，包装成一个 ServerSocket 类。
 * 在 ServerSocket 中一个原生的 BSD Socket 和一个 ev_io 是 一一对应（1:1）的关系
 * libev 就是借助一个 ev_io 来观测/监视/监听一个 BSD Socket（server_socket）。
 */

class TCPServer;

class ServerSocket
{
private:
    int _socket;
    ev::io _io;
    TCPServer *_server;  // “反向”指向 server_socket 的 TCPServer对象。

    void warnAndExit(const char *msg);
    void perrorAndExit(const char *msg);

public:
    ServerSocket(TCPServer *server);

    ~ServerSocket();

    void socket();

    void bind(const char *ip, unsigned short port);

    void listen();

    int accept();

    void close();

    void ServerSocketCallBack(ev::io &io, int revents);

    bool isAvailable();

//    void setServer(TCPServer *server);

};

#endif //TCPSERVER_DEMO6_SERVERSOCKET_H


