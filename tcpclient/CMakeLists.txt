add_executable(tcpclient main.c tcpclientloop.c tcpclientloop.h)
target_link_libraries(tcpclient PUBLIC common)