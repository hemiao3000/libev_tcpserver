//
// Created by ben on 19-2-27.
//

#include "../include/ClientSocket.h"

ClientSocket::ClientSocket(int client_socket, TCPServer *server) {
    if (client_socket == INVALID_SOCK) {
        warn("ClientSocket构造函数参数错误");
        exit(EXIT_FAILURE);
    }

    _client_socket = client_socket;
    _server = server;

    debug("让libev开始监听这个新的client_sock");
    _io.set(_client_socket, EV_READ);
    _io.set<ClientSocket, &ClientSocket::CallBack>(this);
    _io.start();
}

void ClientSocket::CallBack(ev::io &io, int revents) {
    long n = recvData();
    if (n == 0) {
        io.stop();  // io.start() 的反操作
                    // 从“关注清单”中移除本io
                    // 让 libev 的pool不再关系 _client_socket 是否有数据可读
        _server->removeClientSocket(this);
    }
}

long ClientSocket::recvData() {
    if (_client_socket == INVALID_SOCK) {
        warn("recvData(): 参数错误");
        exit(EXIT_FAILURE);
    }

    char buf[1024] = {};
    long n = recv(_client_socket, buf, 1023, 0);
    if (n == -1) {
        warn("recv系统调用出错!");
        handler_error1("recv()");
    }
    else if (n == 0) {
        info("客户端断开连接");
        ::close(_client_socket);
    }
    else {
        buf[n] = '\0';
        printf("INFO: 接受到客户端数据：%s\n", buf);
    }
}

void ClientSocket::sendData() {

}
