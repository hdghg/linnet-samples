#include <stdio.h>
#include <string.h>
#include <sys/poll.h>
#include <termios.h>
#include <unistd.h>

#include "io.h"

void nonblock() {
  struct termios ttystate;

  //get the terminal state
  tcgetattr(STDIN_FILENO, &ttystate);

  //turn off canonical mode
  ttystate.c_lflag &= ~(unsigned int) ICANON;
  //minimum of number input read.
  ttystate.c_cc[VMIN] = 1;
  tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

int main() {
  char line[129];
  struct pollfd fds[1] = {{STDIN_FILENO, POLLIN}};
  int res;
  nonblock();
  printf("Starting tcpserv\n");
  //  res = poll(fds, 1, 3000);
  //  printf("Res: %d\n", res);


  memset(line, '\0', sizeof(line));
  while (NULL == NbReadLine(line)) {
    //printf(".");
  }
  printf("%s\n", line);

  return 0;
}