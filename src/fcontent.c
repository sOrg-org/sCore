#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("\e[34m\U000f0dca \e[0mUsage: fcontent <file>\n");
    return 1;
  }

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    printf("\e[34m\U000f0dca \e[0mUsage: fnew <file> <opts>\n"
           "  -h, --help    Show this message\n"
           "  -n, --nums    Show line numbers\n");
    return 0;
  }

  int nums = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--nums") == 0) {
      nums = 1;
    }
  }

  FILE *file;
  file = fopen(argv[1], "r");

  if (file == NULL) {
    printf("\e[31m\U000f0dca \e[0mFailed to open file %s\n", argv[1]);
    return 1;
  }

  printf("\e[32m\U000f0dca \e[0mContent of %s:\n", argv[1]);

  printf("\e[90m");

  for (int i = 0; i < 64; i++) {
    printf("\u2014");
  }

  printf("\e[0m\n");

  int ch;
  int line = 1;

  if (nums) {
    printf("\e[90m%4d \e[0m", line++);
  }

  while ((ch = fgetc(file)) != EOF) {
    putchar(ch);

    if (ch == '\n' && nums) {
      printf("\e[90m%4d \e[0m", line++);
    }
  }

  printf("\n\e[90m");

  for (int i = 0; i < 64; i++) {
    printf("\u2014");
  }

  printf("\e[0m\n");

  return 0;
}
