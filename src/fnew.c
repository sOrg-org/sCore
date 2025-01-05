#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("\e[34m\U0000f05a \e[0mUsage: fnew <file> <opts>\n"
           "  Run \"fnew -h\" for help\n");
    return 1;
  }

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    printf(
        "\e[34m\U0000f05a \e[0mUsage: fnew <file> <opts>\n"
        "  -h,  --help                Show this message\n"
        "  -nb, --nobackup            Do not backup the file if overwritten\n"
        "  -s,  --size <int>          Fill the file with <int> null bytes\n"
        "  -c,  --content <string>    Fill the file with initial content\n");
    return 0;
  }

  int no_backup = 0;

  for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "-nb") == 0 || strcmp(argv[i], "--nobackup") == 0) {
      no_backup = 1;
    }
  }

  if (!no_backup) {
    struct stat buffer;

    if (stat(argv[1], &buffer) == 0) {
      char backup_name[128];
      snprintf(backup_name, sizeof(backup_name), "%s.bac", argv[1]);

      if (rename(argv[1], backup_name) == 0) {
        printf("\e[32m\U000f0752 \e[0mBackup of %s created as %s\n", argv[1],
               backup_name);
      } else {
        fprintf(stderr, "\e[31m\U000f0752 \e[0mFailed to backup file %s\n",
                argv[1]);
        return 1;
      }
    }
  }

  FILE *file = fopen(argv[1], "w");

  if (file == NULL) {
    fprintf(stderr, "\e[31m\U000f0752 \e[0mFailed to create file %s\n",
            argv[1]);
    return 1;
  }

  for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--content") == 0) {
      fprintf(file, "%s", argv[i + 1]);

      i++;
    }

    if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--size") == 0) {
      for (int j = 0; j < atoi(argv[i + 1]); j++) {
        fprintf(file, "%c", 0);
      }

      i++;
    }
  }

  fclose(file);

  printf("\e[32m\U000f0752\e[0m Created file %s\n", argv[1]);
  return 0;
}

