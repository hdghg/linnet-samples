//
// Created by sieben on 26.07.2022.
//

#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include "common.h"

int CreateSocket(int *sock, int family, int type, int protocol) {
    *sock = socket(family, type, protocol);
    if (-1 == *sock) {
        if (EPROTONOSUPPORT == errno) {
            printf("Protocol is not supported by the system\n");
        } else {
            printf("CreateSocket() failed with error code %d\n", errno);
        }
        return -1;
    }
    return 0;
}