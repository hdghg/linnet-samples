#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <arpa/inet.h>	//inet_addr
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
  int socket_desc, on = 1, timeout = 3 * 60 * 1000;
  char *message = "xyu1";
  struct pollfd fds[1];
  struct sockaddr_in server_addr;
  int res;
  char buffer[130];
  {
    memset(buffer, 0, sizeof(buffer));
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.156");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7171);
  }

  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == socket_desc) {
    printf("Couldn't create a socket\n");
    return -1;
  }
  //if (ioctl(socket_desc, FIONBIO, (char*)&on) < 0) {
  //  printf("Couldn't switch no non-blocking mode\n");
  //  return -1;
  //}
  if (connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    // errno = 115 (EINPROGRESS)
    printf("Connect failed: %d\n", errno);
    return -1;
  }
  printf("Connected successfully\n");
  fds[0].fd = socket_desc;
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


