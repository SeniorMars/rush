#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SIZE 6
#define DEFAULT_BUFFER_SIZE 10

char *args[SIZE]; // We have to fix to have dynamic memory based on length of
                  // read_line!!
char *read_line() {
  int size = DEFAULT_BUFFER_SIZE;
  char *str;
  str = (char *)calloc(size, sizeof(char));
  char c;
  c = getchar();
  int i = 0;
  while (c != '\n') {
    if (i >= size) {
      size = size * 2;
      str = (char *)realloc(str, size);
    }
    str[i] = c;
    c = getchar();
    ++i;
  }
  str[i] = '\0';
  return str;
}

char **parse_args(char *line) {
  for (int i = 0; line; i++) {
    // I think we should perhaps try to separate by ";" first and
    // call the this same function. Like recursively!
    // We would have to allocate enough space for the array arcs
    args[i] = strsep(&line, " ");
  }
  return args;
}
