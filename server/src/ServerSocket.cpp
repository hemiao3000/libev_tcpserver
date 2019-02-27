#include "../include/ServerSocket.h"

ServerSocket::ServerSocket() {
    _server_socket = INVALID_SOCK;
}

ServerSocket::~ServerSocket() {
    close();
}

/**
 * 包装原生 socket 函数
 */
void ServerSocket::socket() {
    if (_server_socket != INVALID_SOCK) {
        warn("socket(): 参数错误");
        exit(EXIT_FAILURE);
    }

    _server_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_server_socket == INVALID_SOCK)
        handler_error1("socket()");

    info("成功创建服务端Socket");

    _io.set(_server_socket, EV_READ);
    _io.set<ServerSocket, &ServerSocket::ServerSocketCallBack>(this);
    _io.start();
}

/**
 * 包装原生 listen 函数
 */
void ServerSocket::bind(const char *ip, short port) {
    if (_server_socket == INVALID_SOCK) {
        warn("bind(): 参数错误");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    if (::bind(_server_socket, (sockaddr *) &server_addr, sizeof(sockaddr_in)) == -1)
        handler_error1("bind()");

    info("成功绑定IP和端口号");
}

/**
 * 包装原生 listen 函数
 */
void ServerSocket::listen() {
    if (_server_socket == INVALID_SOCK) {
        warn("listen(): 参数错误");
        exit(EXIT_FAILURE);
    }

    if (::listen(_server_socket, 5) == -1)
        handler_error1("listen()");

    info("成功开始监听连接请求...");
}

/**
 * 包装原生 accept 函数
 */
int ServerSocket::accept() {
    if (_server_socket == INVALID_SOCK) {
        warn("accept(): 参数错误");
        exit(EXIT_FAILURE);
    }

    int cli_sock = ::accept(_server_socket, nullptr, nullptr);
    if (cli_sock == INVALID_SOCK)
        handler_error1("accept()");

    info("成功接受客户端连接请求");
    return cli_sock;
}

/**
 * 关闭 server_socket
 */
void ServerSocket::close() {
    if (_server_socket == INVALID_SOCK)
        return;

    ::close(_server_socket);
    _server_socket = INVALID_SOCK;
    info("成功关停服务端");
}

/**
 * server_socket 有数据可读时的回调函数
 */
void ServerSocket::ServerSocketCallBack(ev::io &io, int revents) {
    int client_sock = accept();
    ClientSocket *clientSocket = new ClientSocket(client_sock, _server);
    _server->addClientSocket(clientSocket);
}

/**
 * 判断 server_socket 是否可用
 */
bool ServerSocket::isAvailable() {
    return _server_socket != INVALID_SOCK;
}

/**
 * 为 server_socket 设置其“所属”的 TCPServer
 */
void ServerSocket::setServer(TCPServer *server) {
    _server = server;
}

