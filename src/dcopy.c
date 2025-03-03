#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#define mkdir(path, mode) _mkdir(path)
#define chmod _chmod
#endif

int copy_file(char *src, char *dest);
int copy_dir(char *path, char *dest_path);

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("\e[34m\U0000f05a \e[0mUsage: fcopy <path> <new_path>\n");
    return 1;
  }

  if (copy_dir(argv[1], argv[2]) == 0) {
    printf("\e[32m\U000f19ec \e[0mCopied directory %s to %s\n", argv[1],
           argv[2]);
  } else {
    fprintf(stderr, "\e[31m\U000f19ec \e[0mError copying directory %s to %s\n",
            argv[1], argv[2]);
    return 1;
  }

  return 0;
}

int copy_dir(char *path, char *dest_path) {
  struct dirent *entry;
  DIR *dir = opendir(path);

  if (dir == NULL) {
    fprintf(stderr, "\e[31m\U000f19ec \e[0mError opening directory %s\n", path);
    return -1;
  }

  if (mkdir(dest_path, 0777) != 0) {
    fprintf(stderr, "\e[31m\U000f19ec \e[0mError creating directory %s\n",
            dest_path);
    closedir(dir);
    return -1;
  }

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    char full_path[1024], dest_full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
    snprintf(dest_full_path, sizeof(dest_full_path), "%s/%s", dest_path,
             entry->d_name);

    struct stat statbuf;

    if (stat(full_path, &statbuf) == 0) {
      if (S_ISDIR(statbuf.st_mode)) {
        if (copy_dir(full_path, dest_full_path) != 0) {
          closedir(dir);
          return -1;
        }
      } else {
        if (copy_file(full_path, dest_full_path) != 0) {
          closedir(dir);
          return -1;
        }
      }
    } else {
      fprintf(stderr, "\e[31m\U000f19ec \e[0mError getting stat of file %s\n",
              full_path);
      closedir(dir);
      return -1;
    }
  }

  closedir(dir);
  return 0;
}

int copy_file(char *src, char *dest) {
  FILE *src_file = fopen(src, "r");

  if (src_file == NULL) {
    fprintf(stderr, "\e[31m\U000f19ec \e[0mError opening source file %s\n",
            src);
    return -1;
  }

  FILE *dest_file = fopen(dest, "w");

  if (dest_file == NULL) {
    fprintf(stderr, "\e[31m\U000f19ec \e[0mError opening destination file %s\n",
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
