#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  DIR *dir;
  struct dirent *entry;
  struct stat entry_stat;

  char dir_name[128] = ".";

  int show_mode = 0;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      for (int j = 1; j < (int)strlen(argv[i]); j++) {
        if (argv[i][j] == 'a')
          show_mode = 1;
        if (argv[i][j] == 'A')
          show_mode = 2;
      }
    } else {
      strcpy(dir_name, argv[i]);
    }
  }

  dir = opendir(dir_name);

  if (dir == NULL) {
    printf("\e\[31m\U000f178a \e[0mFailed to open %s\n", dir_name);
    return 1;
  }

  printf("\e[32m\U000f178a \e[0mContent of %s:\n", dir_name);

  printf("\e[90m");

  for (int i = 0; i < 64; i++) {
    printf("\u2014");
  }

  printf("\e[0m\n");

  while ((entry = readdir(dir)) != NULL) {
    char entry_full_name[512];
    sprintf(entry_full_name, "%s/%s", dir_name, entry->d_name);

    stat(entry_full_name, &entry_stat);

    int can_print = 0;
    char icon[8];

    if (S_ISREG(entry_stat.st_mode)) {
      if (entry->d_name[0] == '.') {
        strcpy(icon, "\U000f0dca");
      } else {
        strcpy(icon, "\U000f0214");
      }
    }
    if (S_ISDIR(entry_stat.st_mode)) {
      if (entry->d_name[0] == '.') {
        strcpy(icon, "\U000f178a");
      } else {
        strcpy(icon, "\U000f024b");
      }
    }

    if (show_mode == 0) {
      if (entry->d_name[0] == '.') {
        continue;
      }
      can_print = 1;
    } else if (show_mode == 1) {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
        continue;
      }
      can_print = 1;
    } else if (show_mode == 2) {
      can_print = 1;
    }

    if (can_print) {
      printf("\e[34m%s \e[0m%s", icon, entry->d_name);

      if (S_ISREG(entry_stat.st_mode)) {
        for (int i = 0; i < 24 - (int)strlen(entry->d_name); i++) {
          printf(" ");
        }

        printf("%.2f\e[90mkb\e[0m", (float)entry_stat.st_size / 1024);
      }

      printf("\n");
    }
  }

  printf("\e[90m");

  for (int i = 0; i < 64; i++) {
    printf("\u2014");
  }

  printf("\e[0m\n");

  return 0;
}
