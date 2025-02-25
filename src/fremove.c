#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <io.h>
#define chmod _chmod
#endif

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("\e[34m\U0000f05a \e[0mUsage: fremove [-f] <file1> <file2> ...\n");
    return 1;
  }

  int exit_code = 0;
  int force = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--force") == 0) {
      force = 1;
    }
  }

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      continue;
    }

    if (force) {
      if (chmod(argv[1], 0777) != 0) {
        fprintf(
            stderr,
            "\e[31m\U000f1aa1 \e[0mError modifying permissions of file %s\n",
            argv[1]);
        exit_code = 1;
      }
    }

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
