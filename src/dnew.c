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
    printf("\e[34m\U000f0257 \e[0mUsage: dnew <dir> \n");
    return 1;
  }

  if (mkdir(argv[1], 0777) == 0) {
    printf("\e[32m\U000f0257 \e[0mCreated directory %s\n", argv[1]);
  } else {
    fprintf(stderr, "\e[31m\U000f0257 \e[0mError creating directory %s\n",
            argv[1]);
    return 1;
  }

  return 0;
}
