#include <iostream>
#include "include/ClientSocket.h"
#include "include/TCPClient.h"

int main() {
    TCPClient client;

    client.start("127.0.0.1", 9876);

    return 0;
}