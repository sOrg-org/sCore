#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("\e[34m\U0000f05a \e[0mUsage: fnew <file1> <file2>...\n");
    return 1;
  }

  for (int i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "w");

    if (file == NULL) {
      fprintf(stderr, "\e[31m\U000f0752 \e[0mFailed to create file %s\n",
              argv[i]);
      return 1;
    }

    fclose(file);
    printf("\e[32m\U000f0752\e[0m Created file %s\n", argv[i]);
  }

  return 0;
}
