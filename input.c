#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SIZE 6
#define DEFAULT_BUFFER_SIZE 10

/* char *args[SIZE]; // We have to fix to have dynamic memory based on length of
 */
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

char *args[DEFAULT_BUFFER_SIZE]; // arugments
char **parse_args(char *line) {
    // dynamic allocate buffer size
  for (int i = 0; line; i++) {
    // I think we should perhaps try to separate by ";" first and
    // call the this same function. Like recursively.
    // We would have to allocate enough space for the array arcs
    args[i] = strsep(&line, " ");
    /* printf("%s\n", args[i]); */
  }
  return args;
}

void count(int *cmds, int *args, char *line) {
  for (int i = 0; i < (int) strlen(line); i++) {
    if (line[i] == ' ') {
      (*args)++;
    }
    if (line[i] == ';') {
      (*cmds)++;
    }
  }
}


int main() {
  // all the below should be in a while loop. Unless when we parse line it's "quit"
  char *line = read_line();
  int commands = 1, arguments = 1; // start at once because there will always be one command ad one argument
  int *cmdp = &commands, *argsp = &arguments;
  count(cmdp, argsp, line); // gets number of arguments and commands
  printf("%d\n", *argsp);
  // parse amount of arguments;
  /* for (int i = 0; i < strlen(line); i++) { */
  /*   printf("%c\n", line[i]); */
  /* } */
  /* int len = strlen(line); */
  char **args = parse_args(line);
  execvp(args[0], args);
  return 0;
}
