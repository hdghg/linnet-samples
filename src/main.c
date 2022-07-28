#include <stdio.h>

#include "../common/args.h"
#include "tcpclientloop.h"

int main(int argc, char **argv) {
  struct samples_args args = {"127.0.0.1"};

  printf("Starting tcpclient\n");
  ParseArgs(&args, argc, argv);

  return ClientMainLoop(args.address);
}


