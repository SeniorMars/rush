#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <linux/limits.h>
#define DEFAULT_BUFFER_SIZE 10

/* char *args[SIZE]; // We have to fix to have dynamic memory based on length of
 */
// read_line!!
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

char *trim(char *string)
{
  char *end = string + strlen(string);
  while (isspace(*string))
    string++;
  while(isspace(*--end));
  *(end+1)='\0';
  return string;
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

// prompt for our program
int prompt()
{
  char user[PATH_MAX + 1];
  char host[PATH_MAX + 1];
  char cwd[PATH_MAX + 1];
  if (cuserid(user) != '\0')
  {
    printf("%s", user);
  }
  else
  {
    perror("cuserid error");
    return 1;
  }
  if (gethostname(host, sizeof(host)) != -1)
  {
    printf("@%s:", host);
  }
  else
  {
    perror("gethosename error");
    return 1;
  }
  if (getcwd(cwd, sizeof(cwd)) != NULL)
  {
    printf("%s>> ", cwd);
  }
  else
  {
    perror("getcwd() error");
    return 1;
  }
  return 0;
}

int main()
{
  while (1)
  {
    prompt();
    char *line = read_line();
    /* int commands = 1, arguments = 1; // start at one because there will always be */
    /*                                  // one command ad one argument */
    /* int *cmdp = &commands, *argsp = &arguments; */
    /* count(cmdp, argsp, line); // gets number of arguments and commands */
    /* char arr[*argsp]; */
    /* for (int i = 0; i < (int)strlen(arr); i++) { */
    /*   printf("%c\n", arr[i]); */
    /* } */
    /* printf("%d\n", *argsp); */
    /* int len = strlen(line); */
    if (strlen(line) > 0)
    {
      char **cmds = parse_args(line, ";");
      char **p = cmds;
      for (char *command = *p; command; command = *++p)
      {
        char **args = parse_args(command, " ");
        if (strcmp(args[0], "exit") == 0)
        {
          printf("exiting...\n");
          free(line);
          free(args);
          free(cmds);
          goto end;
        }
        exec(args);
        free(args);
      }
      free(cmds);
    }
    free(line);
  }
end:
  return 0;
}