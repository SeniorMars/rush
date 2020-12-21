#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Colors
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

char *trim(char *string) {
  char *end = string + strlen(string);
  while (isspace(*string))
    string++;
  while (isspace(*--end))
    ;
  *(end + 1) = '\0';
  return string;
}

void greet() {
  printf(RED
         "\n _____  _    _  _____ _    _ \n|  __ \\| |  | |/ ____| |  | |\n| "
         "|__) | |  | | (___ | |__| |\n|  _  /| |  | |\\___ \\|  __  |\n| | \\ "
         "\\| |__| |____) | |  | |\n|_|  \\_\\\\____/|_____/|_|  |_|\n" RESET);
  printf("\nEisuke Hirota, Amit Prasad, Karl Hernandez\n\nRun \"exit\" to "
         "terminate.\n");
}

// prompt for our program
int prompt() {
  char user[PATH_MAX + 1];
  char host[PATH_MAX + 1];
  char cwd[PATH_MAX + 1];
  if (cuserid(user) != '\0') {
    printf(YEL "%s", user);
  } else {
    perror("cuserid error");
    return 1;
  }
  if (gethostname(host, sizeof(host)) != -1) {
    printf("@%s:", host);
  } else {
    perror("gethostname error");
    return 1;
  }
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf(CYN "%s" RESET "$ ", cwd);
  } else {
    perror("getcwd() error");
    return 1;
  }
  return 0;
}

void count_commands(int *cmds, int *args, char *line) {
  for (int i = 0; i < (int)strlen(line); i++) {
    if (line[i] == ' ') {
      (*args)++;
    }
    if (line[i] == ';') {
      (*cmds)++;
    }
  }
}
int count_characters(char *str, const char *to_count) {
  int count = 0;
  for (int i = 0; i < (int)strlen(str); ++i) {
    if (str[i] == *to_count)
      ++count;
  }
  return count;
}

void make_history(char *line) {
  int file, w, linebreak;
  file = open(".rush_hist", O_APPEND | O_WRONLY | O_CREAT, 0644);
  if (file == -1) {
    printf("Open rush_hist failed: %d, %s\n", errno, strerror(errno));
    exit(1);
  }
  w = write(file, line, sizeof(strlen(line)));
  char ln = '\n';
  linebreak = write(file, &ln, sizeof(char));
  if (w == -1 || linebreak == -1) {
    printf("Writing to rush_hist failed: %d, %s\n", errno, strerror(errno));
    exit(1);
  }
  close(file);
}
