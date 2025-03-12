#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_env_range(char *envp[], int *range, int raw);
void print_env_specific(int raw, char *specific_name);

int main(int argc, char *argv[], char *envp[]) {
  int raw = 0;
  int range[] = {-1, -1};
  int specific = 0;
  char *specific_name = NULL;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0) {
      printf("\e[34m\U0000f05a \e[0mUsage: senv [-h] [-r] [-rf: int: 0] [-rt: "
             "int: -1] [-s: string]\n"
             "         -h              Show this message and exit\n"
             "         -r              Print in raw mode\n"
             "         -rf: int: 0     Range from\n"
             "         -rt: int: -1    Range to\n"
             "         -s: string      Print a specific variable only\n");
      return 0;
    }

    if (strcmp(argv[i], "-r") == 0)
      raw = 1;

    if (strcmp(argv[i], "-rf") == 0) {
      if (atoi(argv[i + 1]) != 0) {
        range[0] = atoi(argv[i + 1]);
      } else {
        printf("\e[31m\U0000f52f\e[0m -rf: int expected, got \"%s\"\n",
               argv[i + 1]);
        return 1;
      }
    }

    if (strcmp(argv[i], "-rt") == 0) {
      if (atoi(argv[i + 1]) != 0) {
        range[1] = atoi(argv[i + 1]);
      } else {
        printf("\e[31m\U0000f52f\e[0m -rt: int expected, got \"%s\"\n",
               argv[i + 1]);
        return 1;
      }
    }

    if (strcmp(argv[i], "-s") == 0) {
      if (argv[i + 1] != NULL) {
        specific = 1;
        specific_name = &argv[i + 1][0];
      } else {
        printf("\e[31m\U0000f52f\e[0m -s: string expected, got (null)\n");
        return 1;
      }
    }
  }

  if (specific)
    print_env_specific(raw, specific_name);
  else
    print_env_range(envp, range, raw);

  return 0;
}

void print_env_range(char *envp[], int *range, int raw) {
  int vars_total = 0;

  for (int i = 0; envp[i] != NULL; i++)
    vars_total++;

  if (!raw) {
    printf("\e[32m\U000f100d\e[0m Environment variables (%d Total)\n",
           vars_total);
    printf("\e[90m");

    for (int i = 0; i < 128; i++)
      printf("─");

    printf("\e[0m\n");
  }

  if (range[0] == -1)
    range[0] = 0;
  if (range[1] == -1)
    range[1] = vars_total;

  for (int i = range[0]; i < range[1]; i++) {
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
}

void print_env_specific(int raw, char *specific_name) {
  if (raw) {
    printf("%s=%s\n", specific_name, getenv(specific_name));
  } else {
    printf("\e[32m\U000f100d\e[0m ");
    printf("%s", specific_name);

    for (int j = 0; j < 32 - (int)strlen(specific_name); j++)
      printf(" ");

    printf("    \e[90m│\e[0m    ");

    if (getenv(specific_name) != NULL)
      printf("%s", getenv(specific_name));
    else
      printf("\e[90mNot found\e[0m");

    printf("\n");
  }
}
