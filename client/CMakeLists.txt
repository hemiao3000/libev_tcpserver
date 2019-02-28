cmake_minimum_required(VERSION 3.13)
project(client)

set(CMAKE_CXX_STANDARD 11)

link_libraries(ev)

add_executable(client 
        main.cpp
        src/ClientSocket.cpp
        src/TCPClient.cpp
        include/Message.h)

target_link_libraries(client ev)
