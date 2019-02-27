#include "../include/ClientSocket.h"

ClientSocket::ClientSocket() {
    _socket = INVALID_SOCK;
}

ClientSocket::~ClientSocket() {
    close();
}

void ClientSocket::socket() {
    if (_socket != INVALID_SOCK) {
        warn("socket(): 参数错误");
        exit(EXIT_FAILURE);
    }

    _socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_socket == INVALID_SOCK)
        handler_error1("socket()");

    info("成功创建Socket");
}

void ClientSocket::connect(const char *ip, short port) {
    if (_socket == INVALID_SOCK) {
        warn("connect(): 参数错误");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    if (::connect(_socket, (sockaddr *) &server_addr, sizeof(sockaddr_in)) == -1)
        handler_error1("connect()");

    info("成功发起连接");
}

void ClientSocket::close() {
    if (_socket == INVALID_SOCK)
        return;

    ::close(_socket);
    _socket = INVALID_SOCK;

    info("成功断开连接");
}

bool ClientSocket::isAvailable() {
    return _socket != INVALID_SOCK;
}

