#include "../include/TCPServer.h"

TCPServer::TCPServer() {
    _clientSocketVec = new std::vector<ClientSocket *>();
    _serverSocket = new ServerSocket(this);
}

TCPServer::~TCPServer() = default;

void TCPServer::start(const char *ip, unsigned short port) {
    _serverSocket->socket();
    _serverSocket->bind(ip, port);
    _serverSocket->listen();

    _loop.run(0);
}

void TCPServer::stop() {
    _loop.break_loop(ev::ONE);

    if (_serverSocket != nullptr)
        _serverSocket->close();

    for (auto it = _clientSocketVec->begin(); it != _clientSocketVec->end(); it++) {
        (*it)->close();
    }

    _clientSocketVec->clear();
}

bool TCPServer::isRunning() {
    return _serverSocket->isAvailable();
}

void TCPServer::registerClientSocket(ClientSocket *clientSock) {
    debug("TCPServer新增一个客户端连接");
    _clientSocketVec->push_back(clientSock);
}

void TCPServer::unregisterClientSocket(ClientSocket *clientSock) {
    debug("TCPServer减少一个客户端连接");
    for (auto it = _clientSocketVec->begin();
         it != _clientSocketVec->end(); it++) {
        if (clientSock == *it) {
            _clientSocketVec->erase(it);
            break;
        }
    }
}
