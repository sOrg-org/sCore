#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("\e[34m\U0000f05a \e[0mUsage: fnew <file1> <file2> ...\n");
    return 1;
  }

  int exit_code = 0;

  for (int i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "w");

    if (file == NULL) {
      fprintf(stderr, "\e[31m\U000f0752 \e[0mFailed to create file %s\n",
              argv[i]);
      exit_code = 1;
    } else {
      fclose(file);
      printf("\e[32m\U000f0752\e[0m Created file %s\n", argv[i]);
    }
  }

  return exit_code;
}
