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

char *args[DEFAULT_BUFFER_SIZE]; // DEFAULT_BUFFER_SIZE represents number of arguments size
char **parse_args(char *line)
{
  // dynamic allocate buffer size
  //
  /* char **args = 0; */
  /* int args = 0, cmd = 0; */
  /* char *p = line; */
  /* while (*p) { */
  /*   if (*p == ' ') { */
  /*     args++; */
  /*   } else if (*p == ';') { */
  /*     cmd++; */
  /*   } */
  /* } */
  // dynamic allocate buffer size is a problem
  for (int i = 0; line; i++)
  {
    // I think we should perhaps try to separate by ";" first and
    // call the this same function. Like recursively.
    // We would have to allocate enough space for the array arcs
    args[i] = strsep(&line, " ");
    /* printf("%s\n", args[i]); */
  }
  return args;
}

void exec(char **args)
{
  int c, status;
  printf("---Initial msg to check---\n");

  c = fork();
  if (!c)
  {
    execvp(args[0], args);
  }
  else
  {
    wait(&status);
    printf("---Command executed---\n");
  }
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
      char **args = parse_args(line);
      if (strcmp(args[0], "exit") == 0)
      {
        printf("exiting...\n");
        break;
      }

      exec(args);
    }
    free(line);
  }
  return 0;
}