#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("\e[34m\U0000f05a \e[0mUsage: dmove <path> <new_path>\n"
           "  Can also be used to rename directories\n");
    return 1;
  }

  if (rename(argv[1], argv[2]) == 0) {
    printf("\e[32m\U000f0252 \e[0mMoved directory %s to %s\n", argv[1],
           argv[2]);
  } else {
    fprintf(stderr, "\e[31m\U000f0252 \e[0mError moving directory %s to %s\n",
            argv[1], argv[2]);
    return 1;
  }

  return 0;
}
