#include "../include/TCPClient.h"

void TCPClient::start(const char *ip, short port) {
    _socket.socket();
    _socket.connect(ip, port);

    _timer.set(10, 0);
    _timer.set<TCPClient, &TCPClient::TimeOutCallBack>(this);
    _timer.start();

    _loop.run(0);
}

void TCPClient::TimeOutCallBack(ev::timer &timer, int revents) {
    info("5秒钟到期");
    if (_socket.isAvailable())
        _socket.close();

    timer.loop.break_loop(ev::ONE);
}

