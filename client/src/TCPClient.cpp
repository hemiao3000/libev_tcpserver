#include <cassert>
#include "../include/TCPClient.h"
#include "../include/Message.h"

void TCPClient::start(const char *ip, unsigned short port) {
    _socket->socket();
    _socket->connect(ip, port);

    for (int i = 0; i < 10; i++) {
        auto login = new Login("tom", "123456");
        _socket->sendData(login, sizeof(Login));
    }

    for (int i = 0; i < 10; i++) {
        auto logout = new Logout("tom");
        _socket->sendData(logout, sizeof(Logout));
    }

    _timer.set(10, 0);
    _timer.set<TCPClient, &TCPClient::TimeOutCallBack>(this);
    _timer.start();

    _loop.run(0);
}

void TCPClient::stop() {
    assert(_socket != nullptr);
    _socket->close();
}

void TCPClient::TimeOutCallBack(ev::timer &timer, int revents) {
    info("5秒钟到期");
    stop();

    timer.loop.break_loop(ev::ONE);
}

