#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <arpa/inet.h>	//inet_addr
#include <string.h>
#include <errno.h>

#include "socket/common.h"
#include "args.h"

int main(int argc, char **argv) {
  int socket_desc, on = 1, timeout = 3 * 60 * 1000;
  char *message = "xyu1";
  struct pollfd fds[1];
  struct sockaddr_in server_addr;
  struct samples_args args = {"127.0.0.1"};
  int res;
  char buffer[130];
  {
    memset(buffer, 0, sizeof(buffer));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7171);
  }
  ParseArgs(&args, argc, argv);
  server_addr.sin_addr.s_addr = inet_addr(args.address);

  if (-1 == CreateSocket(&socket_desc, AF_INET, SOCK_STREAM, 0)) {
    return -1;
  }
  if (ioctl(socket_desc, FIONBIO, (char*)&on) < 0) {
    printf("Couldn't switch no non-blocking mode\n");
    return -1;
  }
  fds[0].fd = socket_desc;
  fds[0].events = POLLOUT;
  res = poll(fds, 1, timeout);
  if (res < 0) {
    printf("Poll failed with error %d\n", res);
    return -1;
  }
  res = connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (res < 0) {
    if (EINPROGRESS == errno) {
      printf("Connecting to %s\n", args.address);
      res = poll(fds, 1, timeout);
      if (res < 0) {
          printf("Failed to complete non-blocking connect operation. Error %d\n", errno);
          return -1;
      } else if (0 == res) {
          printf("Connection timeout\n");
          return -1;
      } else if (1 == res) {
          printf("Connection completed successfully\n");
      }
    } else {
      printf("Connect failed: %d\n", errno);
      return -1;
    }
  }
  fds[0].events = POLLIN;

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


