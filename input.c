#include "input.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define DEFAULT_BUFFER_SIZE 10

char *read_line()
{
  int size = DEFAULT_BUFFER_SIZE;
  char *str;
  str = (char *)calloc(size, sizeof(char));
  char c;
  c = getchar();
  int i = 0;
  while (c != '\n')
  {
    if (i >= size)
    {
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
  int count = 1;
  for (int i = 0; i < (int)strlen(line); ++i)
  {
    if (line[i] == *to_split)
      ++count;
  }
  char **args = calloc(count + 1, sizeof(char *));
  args[count] = NULL;
  for (int i = 0; p; i++)
  {
    args[i] = trim(strsep(&p, to_split));
  }
  return args;
}

int exec(char **args)
{
  int c, status;

  c = fork();
  if (!c)
  {
    int rc = execvp(args[0], args);
    if (rc == -1)
    {
      printf("Unknown command\n");
      exit(0);
    }
  }
  else
  {
    wait(&status);
  }
  return 0;
}

void count(int *cmds, int *args, char *line)
{
  for (int i = 0; i < (int)strlen(line); i++)
  {
    if (line[i] == ' ')
    {
      (*args)++;
    }
    if (line[i] == ';')
    {
      (*cmds)++;
    }
  }
}