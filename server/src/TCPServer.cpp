//
// Created by ben on 19-2-27.
//

#include "../include/TCPServer.h"

TCPServer::TCPServer() {
    _clientSocketVec = new std::vector<ClientSocket *>();
    _serverSocket = new ServerSocket();
    _serverSocket->setServer(this);
}

TCPServer::~TCPServer() = default;

void TCPServer::start(const char *ip, short port) {
    _serverSocket->socket();
    _serverSocket->bind(ip, port);
    _serverSocket->listen();

    _loop.run(0);
}

void TCPServer::stop() {
    _loop.break_loop(ev::ONE);
}

bool TCPServer::isRunning() {
    return _serverSocket->isAvailable();
}

/**
 * 在服务端建立与客户端的连接后，将客户端client_sock 保存至数组/向量中。
 * 该数组/向量中记录的是此时与TCPServer保持连接的所有的客户端的client_sock
 */
void TCPServer::addClientSocket(ClientSocket *clientSock) {
    debug("TCPServer新增一个客户端连接");
    _clientSocketVec->push_back(clientSock);
}

/**
 * 是 addClientSocket 的反向操作。
 * 在服务端与客户端的断开连接后，将客户端 client_sock 从数组/向量中移除。
 * 该数组/向量中记录的是此时与TCPServer保持连接的所有的客户端的client_sock
 */
void TCPServer::removeClientSocket(ClientSocket *clientSock) {
    debug("TCPServer减少一个客户端连接");
    /**
     * C++（Java也一样）中，如果需要一边循环，一边向容器中添加/删除元素
     * 那么，不同使用普通的 for 循环。只能使用 迭代器循环。
     */
    for(auto it = _clientSocketVec->begin();
        it != _clientSocketVec->end(); it++) {
        if (clientSock == *it) {
            _clientSocketVec->erase(it);
            break;
        }
    }
}
