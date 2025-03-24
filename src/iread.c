#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0) {
      printf("\e[34m\U0000f05a \e[0mUsage: iread [-h] [-m: string]\n"
             "         -h            Show this message and exit\n\n"
             "  To use this in scripts, run:\n"
             "    \e[34minput_variable=$(iread)\e[0m\n"
             "  The input will be stored in \e[32m$input_variable\e[0m\n");
      return 0;
    }
  }

  char input[1024] = {0};

  fgets(input, sizeof(input), stdin);

  if (input[strlen(input) - 1] == '\n')
    input[strlen(input) - 1] = '\0';

  printf("%s", input);

  return 0;
}