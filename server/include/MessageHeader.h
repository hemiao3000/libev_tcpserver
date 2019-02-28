#ifndef SERVER_DEMO2_MESSAGEHEADER_H
#define SERVER_DEMO2_MESSAGEHEADER_H

#include <cstddef>
#include <iostream>

/**
 * :123        数字123。                            通常用于返回的结果，以及作为数组的一部分。
 *             ":1000\r\n"
 *
 * $123        后续是一个123个字符的字符串（不包括\0）。 通常用于返回的结果，以及作为数组的一部分。
 *             "$12\r\nHello World!\r\n"
 *
 * $0          后续是一个空字符串（即，什么实际内容都没有）
 *             "$0\r\n\r\n"
 *
 * $-1          null
 *             "$-1\r\n"
 *
 */
struct DataHeader
{
    short type;          // : or $ or *
    short number;
};

enum CMD_TYPE
{
    CMD_NUMBER,
    CMD_STRING,
    CMD_ARRAY
};

class Command
{
    uint16_t part_count;
    std::vector<const char *> parts;

    void execute() {
        std::string str;
        for (auto it = parts.begin(); it != parts.end(); it++) {
            str.append(*it);
            str.append(" ");
        }

        std::cout << str << std::endl;
    }

    void addPart(const char *str) {
        parts.push_back(str);
    }
};

class Result
{

};




// DataPackage
/*

struct LoginResult
{
    struct DataHeader header = {CMD_LOGIN_RESULT, sizeof(LoginResult)};
    int result;
    char data[92] = {};
};
 */

#endif //SERVER_DEMO2_MESSAGEHEADER_H
