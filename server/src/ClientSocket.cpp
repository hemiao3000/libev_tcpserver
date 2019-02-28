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
        // 将本次 recv 接受到的数据，拷贝到缓存中
        memcpy(_rcv_buf, buf, (unsigned long) recv_size);
        _rcv_buf_pos += recv_size;   // 此时，pos的大小正好就是缓存中数据的字节数

        // 缓存中确保至少有一个包的头部（4个字节）
        // 否则，数据不够，不足以进行处理。等待下次接受数据后再进行判断-处理
        // 不仅要考虑“不够”的情况，也要考虑“多得多的多”的情况：_recv_buf 中可能有好几个完整的数据包
        // 因此，此处时循环判断-处理，而非“一次性“的 if 判断-处理
        while (_rcv_buf_pos >= sizeof(MessageHeader)) {
            auto header = (MessageHeader *) _rcv_buf;

//            printf("收到的命令的代号是：%d\n", header->type);
//            printf("收到的命令的完整数据大小应该是：%d\n", header->size);

            // _rcv_buf 中数据包不完整（有包头，但是后续内容还没收完）
            // 不够一个完整的数据包，无法处理，等着下一次接受数据
            if (_rcv_buf_pos < header->size)
                break;

            handlerMessage(header);         // 对数据进行处理
            unsigned long n = _rcv_buf_pos - header->size;    // 粘包时，“多”出来的下一个包的数据

            memcpy(_rcv_buf, _rcv_buf + header->size, n);
            _rcv_buf_pos = n;
        }

        return recv_size;
    }
}

void ClientSocket::sendData() {

}

void ClientSocket::handlerMessage(MessageHeader *header) {
    switch (header->type) {
        case CMD_LOGIN: {
            auto login = (Login *) header;
            printf("INFO: 登陆命令。用户名：%s，密码：%s\n", login->username, login->password);
            // 向客户端回 LoginResult
            break;
        }
        case CMD_LOGOUT: {
            auto logout = (Logout *) header;
            printf("INFO: 退出命令。用户名：%s\n", logout->username);
            // 向客户端回 LogoutResult
            break;
        }
        default:
            break;
    }
}

void ClientSocket::perrorAndExit(const char *msg) {
    perror(msg);
    if (_server != nullptr)
        _server->stop();
    close();
    exit(EXIT_FAILURE);
}
