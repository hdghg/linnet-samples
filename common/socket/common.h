#ifndef TCPCLIENT_COMMON_H
#define TCPCLIENT_COMMON_H

#define MESSAGE_SIZE 128

int CreateSocket(int *sock, int family, int type, int protocol);

#endif //TCPCLIENT_COMMON_H
