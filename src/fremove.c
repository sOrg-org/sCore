#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("\e[34m\U0000f05a \e[0mUsage: fremove <file>\n");
    return 1;
  }

  if (remove(argv[1]) == 0) {
    printf("\e[32m\U000f1aa1 \e[0mRemoved file %s\n", argv[1]);
  } else {
    fprintf(stderr, "\e[31m\U000f1aa1 \e[0mError removing file %s\n", argv[1]);
    return 1;
  }

  return 0;
}
