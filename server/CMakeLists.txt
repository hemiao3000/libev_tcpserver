cmake_minimum_required(VERSION 3.13)
project(server)

set(CMAKE_CXX_STANDARD 11)

link_libraries(ev)

add_executable(server
        main.cpp
        src/ServerSocket.cpp
        src/ClientSocket.cpp
        src/TCPServer.cpp
)

target_link_libraries(server ev)
