#include <iostream>
#include "include/ServerSocket.h"
#include "include/TCPServer.h"
#include "include/MessageHeader.h"

int main() {

    /*
    TCPServer server;

    server.start("127.0.0.1", 9876);
     */

    const char *str1 = ":1234\r\n";
    const char *str2 = "\r\n";

    printf("%ld\n", strstr(str1, str2) - str1 - 1);

    return 0;
}