//
// Created by ben on 19-2-25.
//

#ifndef TCPSERVER_DEMO2_COMMON_H
#define TCPSERVER_DEMO2_COMMON_H

#include <ev.h>
#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <zconf.h>
#include <cstdlib>

#define debug(msg) do {            \
    printf("DEBUG: %s\n", (msg));  \
} while (0)

#define info(msg) do {            \
    printf("INFO: %s\n", (msg));  \
} while (0)

#define warn(msg) do {            \
    printf("WARN: %s\n", (msg));  \
} while (0)


#define INVALID_SOCK    (-1)
#define INVALID_PORT    (-1)
#define INVALID_IP      (nullptr)

#endif //TCPSERVER_DEMO2_COMMON_H
