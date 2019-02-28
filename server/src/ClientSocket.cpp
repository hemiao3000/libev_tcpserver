#include <cassert>
#include "../include/ClientSocket.h"

ClientSocket::ClientSocket(int client_socket, TCPServer *server) {
    assert(client_socket != INVALID_SOCK);
    assert(server != nullptr);

    _socket = client_socket;
    _server = server;

    debug("向 libev 注册 client_sock");
    _io.set<ClientSocket, &ClientSocket::CallBack>(this);
    _io.start(_socket, EV_READ);
}

void ClientSocket::close() {
    if (_socket == INVALID_SOCK)
        return;

    ::close(_socket);
    _socket = INVALID_SOCK;
}

void ClientSocket::CallBack(ev::io &io, int revents) {
    long n = recvData();
    if (n == 0) {
        io.stop();  // io.start() 的反操作
                    // 从“关注清单”中移除本io
                    // 让 libev 的pool不再关系 _client_socket 是否有数据可读
        _server->unregisterClientSocket(this);
    }
}

long ClientSocket::recvData() {
    assert(_socket != INVALID_SOCK);

    char buf[1024] = {};
    long recv_size = recv(_socket, buf, 1023, 0);
    if (recv_size == -1) {
        perrorAndExit("recv()");
    }
    else if (recv_size == 0) {
        info("客户端断开连接");
        ::close(_socket);
    }
    else {

    }

    return recv_size;
}

void ClientSocket::sendData() {

}


void ClientSocket::handlerMessage(char *rcv_buf) {

}

void ClientSocket::perrorAndExit(const char *msg) {
    perror(msg);
    if (_server != nullptr)
        _server->stop();
    close();
    exit(EXIT_FAILURE);
}
