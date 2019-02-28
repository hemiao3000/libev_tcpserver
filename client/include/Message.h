#ifndef CLIENT_MESSAGE_H
#define CLIENT_MESSAGE_H

#include <cstring>

enum CMD
{
    CMD_LOGIN,
    CMD_LOGIN_RESULT,
    CMD_LOGOUT,
    CMD_LOGOUT_RESULT
};

struct MessageHeader
{
    short type;
    short size;
};

struct Login
{
    struct MessageHeader header = {CMD_LOGIN, sizeof(Login)};
    char username[64] = {};
    char password[64] = {};

    Login(const char *u, const char *p) {
        unsigned long n = (strlen(u) > 64) ? 64 : strlen(u);
        memcpy(username, u, n);

        n = (strlen(p) > 64) ? 64 : strlen(p);
        memcpy(password, p, n);
    }
};

struct Logout
{
    struct MessageHeader header = {CMD_LOGOUT, sizeof(Logout)};
    char username[64] = {};

    Logout(const char *u) {
        unsigned long n = (strlen(u) > 64) ? 64 : strlen(u);
        memcpy(username, u, n);
    }
};

#endif //CLIENT_MESSAGE_H
