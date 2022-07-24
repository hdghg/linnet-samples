#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <string.h>

int main(int argc, char **argv) {
  int socket_desc;
  char *message = "xyu1";
  struct sockaddr_in server_addr;
  {
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.156");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7171);
  }

  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == socket_desc) {
    printf("Couldn't create a socket\n");
    return -1;
  }
  if (connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    printf("Connect failed\n");
    return -1;
  }
  printf("Connected successfully\n");
  
  printf("Size of char: %zu\n", sizeof(char));
  printf("Size of message: %zu\n", strlen(message));
  
  
  return 0;
}


