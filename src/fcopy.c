#include <stdio.h>
#include <stdlib.h>

int copy_file(char *src, char *dest) {
  FILE *src_file = fopen(src, "r");

  if (src_file == NULL) {
    fprintf(stderr, "\e[31m\U000f1a93 \e[0mError opening source file %s\n",
            src);
    return -1;
  }

  FILE *dest_file = fopen(dest, "w");

  if (dest_file == NULL) {
    fprintf(stderr, "\e[31m\U000f1a93 \e[0mError opening destination file %s\n",
            dest);
    return -1;
  }

  char ch;

  while ((ch = fgetc(src_file)) != EOF) {
    putc(ch, dest_file);
  }

  fclose(src_file);
  fclose(dest_file);

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("\e[34m\U0000f05a \e[0mUsage: fcopy <path> <new_path>\n");
    return 1;
  }

  if (copy_file(argv[1], argv[2]) == 0) {
    printf("\e[32m\U000f1a93 \e[0mCopied file %s to %s\n", argv[1], argv[2]);
  } else {
    fprintf(stderr, "\e[31m\U000f1a93 \e[0mError copying file %s to %s\n",
            argv[1], argv[2]);
    return 1;
  }

  return 0;
}
