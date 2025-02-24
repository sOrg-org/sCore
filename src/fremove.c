#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("\e[34m\U0000f05a \e[0mUsage: fremove <file1> <file2> ...\n");
    return 1;
  }

  int exit_code = 0;

  for (int i = 1; i < argc; i++) {
    if (remove(argv[i]) == 0) {
      printf("\e[32m\U000f1aa1 \e[0mRemoved file %s\n", argv[i]);
    } else {
      fprintf(stderr, "\e[31m\U000f1aa1 \e[0mError removing file %s\n",
              argv[i]);
      exit_code = 1;
    }
  }

  return exit_code;
}
