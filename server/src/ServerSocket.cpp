#include <cassert>
#include "../include/ServerSocket.h"

ServerSocket::ServerSocket(TCPServer *server) {
    assert(server != nullptr);

    _socket = INVALID_SOCK;
    _server = server;
}

ServerSocket::~ServerSocket() {
    close();
}

/**
 * 包装原生 socket 函数
 */
void ServerSocket::socket() {
    assert(_socket != INVALID_SOCK);

    _socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_socket == INVALID_SOCK)
        perrorAndExit("socket()");

    info("成功创建服务端Socket");

    _io.set<ServerSocket, &ServerSocket::ServerSocketCallBack>(this);
    _io.start(_socket, EV_READ);
}

/**
 * 包装原生 listen 函数
 */
void ServerSocket::bind(const char *ip, unsigned short port) {
    assert(_socket != INVALID_SOCK);
    assert(ip != INVALID_IP);

    sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    if (::bind(_socket, (sockaddr *) &server_addr, sizeof(sockaddr_in)) == -1)
        perrorAndExit("bind()");

    info("成功绑定IP和端口号");
}

/**
 * 包装原生 listen 函数
 */
void ServerSocket::listen() {
    assert(_socket != INVALID_SOCK);

    if (::listen(_socket, 5) == -1)
        perrorAndExit("listen()");

    info("成功开始监听连接请求...");
}

/**
 * 包装原生 accept 函数
 */
int ServerSocket::accept() {
    assert(_socket != INVALID_SOCK);

    int cli_sock = ::accept(_socket, nullptr, nullptr);
    if (cli_sock == INVALID_SOCK)
        perrorAndExit("accept()");

    info("成功接受客户端连接请求");
    return cli_sock;
}

/**
 * 关闭 server_socket
 */
void ServerSocket::close() {
    if (_socket == INVALID_SOCK)
        return;

    ::close(_socket);
    _socket = INVALID_SOCK;
    info("成功关停服务端");
}

/**
 * server_socket 有数据可读时的回调函数
 */
void ServerSocket::ServerSocketCallBack(ev::io &io, int revents) {
    int client_sock = accept();
    auto clientSocket = new ClientSocket(client_sock, _server);
    _server->registerClientSocket(clientSocket);
}

/**
 * 判断 server_socket 是否可用
 */
bool ServerSocket::isAvailable() {
    return _socket != INVALID_SOCK;
}

void ServerSocket::warnAndExit(const char *msg) {
    printf("WARN: %s\n", msg);
    if (_server != nullptr)
        _server->stop();

    exit(EXIT_FAILURE);
}

void ServerSocket::perrorAndExit(const char *msg) {
    perror(msg);
    if (_server != nullptr)
        _server->stop();
    close();
    exit(EXIT_FAILURE);
}
