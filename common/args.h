#ifndef TCPCLIENT_ARGS_H
#define TCPCLIENT_ARGS_H

struct samples_args {
  char address[16];
};

void ParseArgs(struct samples_args *sa, int argc, char **argv);

#endif //TCPCLIENT_ARGS_H
