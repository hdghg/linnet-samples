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
  printf("flag: %u\n", ttystate.c_lflag);
  ttystate.c_lflag &= ~ICANON;
  ttystate.c_lflag &= ~ECHO;
  //minimum of number input read.
  ttystate.c_cc[VMIN] = 1;
  tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

int main() {
  char line[129];
  struct pollfd fds[1] = {{STDIN_FILENO, POLLIN}};
  int res, c = 0;
  nonblock();
  printf("Starting tcpserv\n");
//  while (c != ']') {
//    res = poll(fds, 1, 3000);
//    printf("Res: %d\n", res);
//    c = getchar();
//    if (127 == c) { // backspace
//      printf("Next is: %d\n", getchar());
//    }
//    printf("Char: %d\n", c);
//  }


  memset(line, '\0', sizeof(line));
  while (NULL == NbReadLine(line)) {
    //printf(".");
  }
  printf("%s\n", line);

  return 0;
}