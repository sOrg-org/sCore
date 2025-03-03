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
#define rmdir(path) _rmdir(path)
#define unlink(path) _unlink(path)
#define chmod _chmod
#endif

int delete_dir(const char *path, int force) {
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
        if (delete_dir(full_path, force) != 0) {
          closedir(dir);
          return -1;
        }
      } else {
        if (force) {
          if (chmod(full_path, 0777) != 0) {
            fprintf(stderr,
                    "\e[31m\U0000eec6 \e[0mError modifying permissions of file "
                    "%s\n",
                    full_path);
            closedir(dir);
            return -1;
          }
        }

        if (unlink(full_path) != 0) {
          fprintf(stderr, "\e[31m\U0000eec6 \e[0mError unlinking file %s\n",
                  full_path);
          closedir(dir);
          return -1;
        }
      }
    } else {
      fprintf(stderr, "\e[31m\U0000eec6 \e[0mError getting stat of file %s\n",
              full_path);
      closedir(dir);
      return -1;
    }
  }

  closedir(dir);

  if (force) {
    if (chmod(path, 0777) != 0) {
      fprintf(stderr,
              "\e[31m\U0000eec6 \e[0mError modifying permissions of "
              "directory "
              "%s\n",
              path);
      closedir(dir);
      return -1;
    }
  }

  if (rmdir(path) != 0) {
    return -1;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("\e[34m\U0000eec6 \e[0mUsage: dremove [-f] <dir1> <dir2> ...\n");
    return 1;
  }

  int exit_code = 0;
  int force = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--force") == 0) {
      force = 1;
    }
  }

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      continue;
    }

    if (delete_dir(argv[i], force) == 0) {
      printf("\e[32m\U0000eec6 \e[0mRemoved directory %s\n", argv[i]);
    } else {
      fprintf(stderr, "\e[31m\U0000eec6 \e[0mError removing directory %s\n",
              argv[i]);
      exit_code = 1;
    }
  }

  return exit_code;
}
