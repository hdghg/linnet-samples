#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <zconf.h>

#include "socket/common.h"
#include "tcpclientloop.h"


// -1 = error
// 0 = ready
int awaitReadiness(int fd) {
  int timeout = 15 * 1000;
  struct pollfd fds[1];
  int res, i;
  memset(fds, 0, sizeof(fds));
  {
    fds[0].fd = fd;
    fds[0].events = POLLIN;
  }
  res = poll(fds, 1, timeout);
  if (res < 0) {
    printf("Failed to complete non-blocking connect operation. Error %d\n", errno);
    return -1;
  } else if (0 == res) {
    printf("Poll timeout\n");
    return -1;
  } else if (1 == res) {
    if (28 == fds[0].revents) {
      printf("poll() returned earlier then expected. Server seem to be offline.\n");
      return -1;
    }
    printf("Connection completed successfully\n");
    for (i = 0; i < res; i++) {
      printf("[%d]: revents = %d\n", i, fds[i].revents);
    }
    return 0;
  }
  return 0;
}

int mainLoop(int socket_desc) {
  int timeout = 3 * 60 * 1000;
  struct pollfd fds[1];
  int res;
  char buffer[130];
  {
    memset(buffer, 0, sizeof(buffer));
    fds[0].fd = socket_desc;
    fds[0].events = POLLIN;
  }
  printf("Ready\n");
  res = poll(fds, 1, timeout);
  if (res < 0) {
    printf("Poll failed with error %d\n", res);
    return -1;
  }
  if (0 == res) {
    printf("No data after %d seconds of wait\n", timeout);
    return 0;
  }
  res = recv(socket_desc, buffer, 128, 0);
  if (res < 0) {
    if (errno != EWOULDBLOCK) {
      printf("recv() failed: %d\n", errno);
      return -1;
    }
    printf("res < 0");
    return 0;
  }
  printf("%d bytes received: %s\n", res, buffer);

  return 0;
}

int ClientMainLoop(char *serverAddressStr) {
  int socket_desc, on = 1;
  struct sockaddr_in server_addr;
  int res;
  {
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(serverAddressStr);
    server_addr.sin_port = htons(7171);
  }
  printf("Starting tcpclient\n");

  if (-1 == CreateSocket(&socket_desc, AF_INET, SOCK_STREAM, 0)) {
    return -1;
  }
  printf("Connecting to %s...\n", serverAddressStr);
  res = connect(socket_desc, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if (res < 0) {
    printf("Connect failed: [%d] %s\n", errno, strerror(errno));
    goto close;
  }
  printf("Connected\n");
  if (ioctl(socket_desc, FIONBIO, (char *) &on) < 0) {
    printf("Couldn't switch no non-blocking mode\n");
    goto close;
  }
  printf("Switched to no non-blocking mode\n");
  mainLoop(socket_desc);

  close: close(socket_desc);
  return 0;
}