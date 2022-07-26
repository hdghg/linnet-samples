#include <string.h>

#include "args.h"

void ParseArgs(struct samples_args *sa, int argc, char **argv) {
  int i;
  for (i = 1; i < argc; i++) {
    if ((argv[i][0] != '-') && (argv[i][0] != '/')) {
      continue;
    }
    switch (argv[i][1]) {
      case 'n':
        if ((i + 1 < argc) && (strlen(argv[i + 1]) < sizeof(sa->address))) {
          strcpy(sa->address, argv[i + 1]);
        }
        break;
      default:
        break;
    }
  }
}
