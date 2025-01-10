#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef _WIN32
#include <direct.h>
#define rmdir(path) _rmdir(path)
#define unlink(path) _unlink(path)
#endif

int delete_dir(const char *path) {
  struct dirent *entry;
  DIR *dir = opendir(path);

  if (dir == NULL) {
    fprintf(stderr, "\e[31m\U0000eec6 \e[0mError opening dir %s\n", path);
    return -1;
  }

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

    struct stat statbuf;

    if (stat(full_path, &statbuf) == 0) {
      if (S_ISDIR(statbuf.st_mode)) {
        if (delete_dir(full_path) != 0) {
          closedir(dir);
          return -1;
        }
      } else {
        if (unlink(full_path) != 0) {
          fprintf(stderr, "\e[31m\U0000eec6 \e[0mError unlinking file %s\n",
                  full_path);
          closedir(dir);
          return -1;
        }
      }
    } else {
      fprintf(stderr, "\e[31m\U0000eec6 \e[0mError reading file %s for stat\n",
              full_path);
      closedir(dir);
      return -1;
    }
  }

  closedir(dir);

  if (rmdir(path) != 0) {
    fprintf(stderr, "\e[31m\U0000eec6 \e[0mError removing directory %s\n",
            path);
    return -1;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("\e[34m\U0000eec6 \e[0mUsage: dremove <dir>\n");
    return 1;
  }

  if (delete_dir(argv[1]) == 0) {
    printf("\e[32m\U0000eec6 \e[0mDirectory %s removed successfully\n",
           argv[1]);
  } else {
    fprintf(stderr, "\e[31m\U0000eec6 \e[0mError removing directory %s\n",
            argv[1]);
    return 1;
  }

  return 0;
}
