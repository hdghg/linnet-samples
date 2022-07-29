#include <stdio.h>
#include <string.h>
#include <sys/poll.h>
#include <unistd.h>

#include "io.h"
#include "socket/common.h"

// Read a line in non-blocking way.
// Expected to be run repeatedly until result is not NULL
// Returns NULL when line is not completed
// Returns pointer to dest argument after user hits ENTER
char* NbReadLine(char *dest) {
  int timeout = 125;
  struct pollfd fds[1];
  size_t len;
  int c;
  {
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
  }
  while (poll(fds, 1, timeout) > 0) {
    len = strlen(dest);
    c = getchar();
    // Tab is ignored
    if ('\t' == c) {
      return NULL;
    }
    // Backspace
    if (127 == c && 0 < len) {
      printf("%c %c", '\010', '\010');
      dest[len - 1] = '\0';
      return NULL;
    }
    if (('\r' == c) || ('\n' == c)) {
      printf("\n");
      return dest;
    }
    if (len < MESSAGE_SIZE) {
      dest[len] = (char) c;
      printf("%c", c);
    }
  }
  return NULL;
}