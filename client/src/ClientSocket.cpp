#include <cassert>
#include "../include/ClientSocket.h"

ClientSocket::ClientSocket() {
    _socket = INVALID_SOCK;
}

ClientSocket::~ClientSocket() {
    close();
}

void ClientSocket::socket() {
    assert(_socket == INVALID_SOCK);

    _socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_socket == INVALID_SOCK)
        perrorAndExit("socket()");

    info("成功创建Socket");
}

void ClientSocket::connect(const char *ip, unsigned short port) {
    assert(_socket != INVALID_SOCK);

    sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    if (::connect(_socket, (sockaddr *) &server_addr, sizeof(sockaddr_in)) == -1)
        perrorAndExit("connect()");

    info("成功发起连接");
}

void ClientSocket::close() {
    if (_socket == INVALID_SOCK)
        return;

    ::close(_socket);
    _socket = INVALID_SOCK;

    info("成功断开连接");
}

void ClientSocket::sendData(void *buf, unsigned long size) {
    long n = send(_socket, buf, size, 0);
}

bool ClientSocket::isAvailable() {
    return _socket != INVALID_SOCK;
}

void ClientSocket::perrorAndExit(const char *msg) {
    perror(msg);
    close();
    exit(EXIT_FAILURE);
}