#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#endif

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("\e[34m\U000f0257 \e[0mUsage: dnew <dir1> <dir2> ...\n");
    return 1;
  }

  int exit_code = 0;

  for (int i = 1; i < argc; i++) {
    if (mkdir(argv[i], 0777) == 0) {
      printf("\e[32m\U000f0257 \e[0mCreated directory %s\n", argv[i]);
    } else {
      fprintf(stderr, "\e[31m\U000f0257 \e[0mError creating directory %s\n",
              argv[i]);
      exit_code = 1;
    }
  }

  return exit_code;
}
