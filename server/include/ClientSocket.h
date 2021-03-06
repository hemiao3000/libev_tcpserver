//
// Created by ben on 19-2-27.
//

#ifndef TCPSERVER_DEMO6_CLIENTSOCKET_H
#define TCPSERVER_DEMO6_CLIENTSOCKET_H

#include <queue>
#include "common.h"
#include "TCPServer.h"
#include "MessageHeader.h"


/**
 * 在TCPServer这一侧
 * 将 client_socket（即，accept函数的返回之）包装成对象。
 * 其中原生的 BSD Socket 和 ev_io 也是一一对应（1:1）的关系
 * 和ServerSocket一样，libev 通过 ev_io 来观测/监视/监听 client_socket 是否有数据可读
 */

class TCPServer;

class ClientSocket
{
private:
    int _socket;
    ev::io _io;
    TCPServer *_server;// “反向”指向 client_socket 的 TCPServer对象。

    ClientSocket() {
        _socket = INVALID_SOCK;
        _server = nullptr;
    }

    void handlerMessage(char *rcv_buf);
    void perrorAndExit(const char *msg);

public:
    ClientSocket(int client_socket, TCPServer *server);

    void close();

    long recvData();

    void sendData();

    void CallBack(ev::io &io, int revents);

};

#endif //TCPSERVER_DEMO6_CLIENTSOCKET_H
