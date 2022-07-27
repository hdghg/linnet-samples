#include "common.h"
#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int CreateSocket(int *sock, int family, int type, int protocol) {
  int synRetries = 2;
  *sock = socket(family, type, protocol);
  if (-1 == *sock) {
    printf("Create socket failed: [%d] %s\n", errno, strerror(errno));
    return -1;
  }
  // set connection timeout to ~7 seconds
  setsockopt(*sock, IPPROTO_TCP, TCP_SYNCNT, &synRetries, sizeof(synRetries));
  return 0;
}