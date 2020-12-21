#include "input.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#define DEFAULT_BUFFER_SIZE 10

char *read_line()
{
  int size = DEFAULT_BUFFER_SIZE;
  char *str;
  str = (char *)calloc(size+1, sizeof(char));
  char c;
  c = getchar();
  int i = 0;
  while (c != '\n')
  {
    if (i >= size)
    {
      size = size * 2;
      //size+1 for null-termination byte.
      str = (char *)realloc(str, size + 1);
    }
    str[i] = c;
    c = getchar();
    ++i;
  }
  str[i] = '\0';
  return str;
}

/*
 * char **parse_args(char *line, char* to_split);
 * *line -> Reference to the string containing the entire line.
 * *to_split -> The delimiter to split the line by
 * Returns:
 * **args -> A list of the split strings
*/
char **parse_args(char *line, const char *to_split)
{
  //
  /* Count the number of resulting strings after the split */
  char *p = line;
  int count = count_characters(line, to_split) + 1;
  char **args = calloc(count + 1, sizeof(char *));
  args[count] = NULL;
  for (int i = 0; p; i++)
  {
    args[i] = trim(strsep(&p, to_split));
  }
  return args;
}