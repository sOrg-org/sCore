#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
  int raw = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0) {
      printf("\e[34m\U0000f05a \e[0mUsage: senv [-r]\n"
             "  -r    Print in raw mode\n");
      return 0;
    }

    if (strcmp(argv[i], "-r") == 0) {
      raw = 1;
    }
  }

  if (!raw) {
    int vars_total = 0;

    for (int i = 0; envp[i] != NULL; i++)
      vars_total++;

    printf("Environment variables (%d Total)\n", vars_total);
    printf("\e[90m");

    for (int i = 0; i < 128; i++)
      printf("─");

    printf("\e[0m\n");
  }

  for (int i = 0; envp[i] != NULL; i++) {
    if (raw) {
      printf("%s\n", envp[i]);
    } else {
      printf("\e[90m%4d\e[0m  ", i);

      char var_name[1024] = {0};
      char val_name[1024] = {0};
      int var_name_len = 0;
      int val_name_len = 0;

      int ch = 0;

      while (envp[i][ch] != '=' && var_name_len < 1024)
        var_name[var_name_len++] = envp[i][ch++];

      ch++;

      while (envp[i][ch] != '\0' && val_name_len < 1024)
        val_name[val_name_len++] = envp[i][ch++];

      printf("%s", var_name);

      for (int j = 0; j < 32 - (int)strlen(var_name); j++)
        printf(" ");

      printf("    \e[90m│\e[0m    ");
      printf("%s\n", val_name);
    }
  }

  if (!raw) {
    printf("\e[90m");

    for (int i = 0; i < 128; i++)
      printf("─");

    printf("\e[0m\n");
  }

  return 0;
}
