cmake_minimum_required(VERSION 3.10)

# set the project name
project(tcpclient)

# add the executable
add_executable(tcpclient src/main.c src/tcpclientloop.c src/tcpclientloop.h src/socket/common.c src/socket/common.h)
