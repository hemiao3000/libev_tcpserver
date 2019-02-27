#include <iostream>
#include "include/ServerSocket.h"
#include "include/TCPServer.h"

int main() {

    TCPServer server;

    server.start("127.0.0.1", 9876);

    return 0;
}