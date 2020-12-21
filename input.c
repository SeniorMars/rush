#include "input.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define DEFAULT_BUFFER_SIZE 10

char *read_line() {
  int size = DEFAULT_BUFFER_SIZE;
  char *str;
  str = (char *)calloc(size + 1, sizeof(char));
  char c;
  c = getchar();
  int i = 0;
  while (c != '\n') {
    if (i >= size) {
      size = size * 2;
      // size+1 for null-termination byte.
      str = (char *)realloc(str, size + 1);
    }
    str[i] = c;
    c = getchar();
    ++i;
  }
  str[i] = '\0';
  return str;
}

char **split_string(char *str, const char *to_split) {
  /* Count the number of resulting strings after the split */
  char *p = str;
  int count = count_characters(str, to_split) + 1;
  char **args = calloc(count + 1, sizeof(char *));
  args[count] = NULL;
  for (int i = 0; p; i++) {
    args[i] = trim(strsep(&p, to_split));
  }
  return args;
}
