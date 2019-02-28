#ifndef SERVER_DEMO2_MESSAGEHEADER_H
#define SERVER_DEMO2_MESSAGEHEADER_H

#include <cstddef>
#include <iostream>

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

    MessageHeader(short t, short s) {
        type = t;
        size = s;
    }
};

struct Login : MessageHeader
{
    char username[64] = {};
    char password[64] = {};

    Login(const char *u, const char *p) : MessageHeader(CMD_LOGIN, sizeof(Login)) {
        unsigned long n = (strlen(u) > 64) ? 64 : strlen(u);
        memcpy(username, u, n);

        n = (strlen(p) > 64) ? 64 : strlen(p);
        memcpy(password, p, n);
    }
};

struct Logout : MessageHeader
{
    char username[64] = {};

    Logout(const char *u) : MessageHeader(CMD_LOGOUT, sizeof(Logout)) {
        unsigned long n = (strlen(u) > 64) ? 64 : strlen(u);
        memcpy(username, u, n);
    }
};

struct LoginResult : MessageHeader
{
    char message[64] = {};
    LoginResult(const char *msg) : MessageHeader(CMD_LOGIN_RESULT, sizeof(LoginResult)) {
        unsigned long n = (strlen(msg) > 64) ? 64 : strlen(msg);
        memcpy(message, msg, n);
    }
};

struct LogoutResult : MessageHeader
{
    char message[64] = {};
    LogoutResult(const char *msg) : MessageHeader(CMD_LOGIN_RESULT, sizeof(LogoutResult)) {
        unsigned long n = (strlen(msg) > 64) ? 64 : strlen(msg);
        memcpy(message, msg, n);
    }
};

#endif //SERVER_DEMO2_MESSAGEHEADER_H
