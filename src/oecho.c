#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int newline = 1;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-n") == 0)
      newline = 0;
  }

  for (int i = 1; i < argc; i++) {
    char *buf = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));

    if (buf == NULL) {
      fprintf(stderr, "\e[31m\U0000f52f \e[0mmalloc() failed allocating %s\n",
              argv[1]);
      return 1;
    }

    strcpy(buf, argv[i]);

    for (int j = 0; j < (int)strlen(buf); j++) {
      if (strncmp(&buf[j], "\\n", 2) == 0) {
        buf[j] = '\n';
        memmove(&buf[j + 1], &buf[j + 2], strlen(buf) - j - 1);
      }

      if (strncmp(&buf[j], "\\e", 2) == 0) {
        buf[j] = '\e';
        memmove(&buf[j + 1], &buf[j + 2], strlen(buf) - j - 1);
      }

      if (strncmp(&buf[j], "\\r", 2) == 0) {
        buf[j] = '\r';
        memmove(&buf[j + 1], &buf[j + 2], strlen(buf) - j - 1);
      }
    }

    printf("%s", buf);

    if (i < argc - 1)
      printf(" ");
  }

  if (newline)
    printf("\n");

  return 0;
}
