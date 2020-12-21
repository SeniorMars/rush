#include "input.h"
#include "commandhandler.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

void exec(char **args)
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
}

void exec_callback(char **args, void (*callback)())
{
    exec(args);
    (*callback)();
}
int stdout_dup;
//Restores stdout from the stdout_dup variable.
void restore_stdout()
{
    dup2(stdout_dup, STDOUT_FILENO);
    close(stdout_dup);
}

void redir_out(char **parts, char **args)
{
    int fd1;
    fd1 = open(parts[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    stdout_dup = dup(STDOUT_FILENO);
    dup2(fd1, STDOUT_FILENO); //redirects stdout to fd1
    close(fd1);
    exec_callback(args, restore_stdout);
    free(parts);
    free(args);
}

int stdin_dup;
//Restores stdout from the stdout_dup variable.
void restore_stdin()
{
    dup2(stdin_dup, STDIN_FILENO);
    close(stdin_dup);
}

void redir_in(char **parts, char **args)
{
    int fd1;
    fd1 = open(parts[1], O_RDONLY, 0644);
    if (fd1 == -1)
    {
        printf("Error: %s\n", strerror(errno));
        free(parts);
        free(args);
        return;
    }
    stdin_dup = dup(STDIN_FILENO);
    dup2(fd1, STDIN_FILENO); //redirects stdout to fd1
    close(fd1);
    exec_callback(args, restore_stdin);
    free(parts);
    free(args);
}

char *expand_tilde(char *str, char *home)
{
    int instances = count_characters(str, "~");
    if (instances == 0)
    {
        return str;
    }
    char *dirstr = calloc(sizeof(char), strlen(str) + (instances * strlen(home)) + 1);
    int i = 0, j = 0;
    while (1)
    {
        if (str[j] == '~')
        {
            strcat(dirstr, home);
            i += strlen(home);
        }
        else
        {
            dirstr[i] = str[j];
            ++i;
        }
        if (str[j] == '\0')
        {
            break;
        }
        ++j;
    }
    return dirstr;
}
void pipe_cmd(char **parts) {
  /* FILE *file = popen(parts[0], "r"); */
  /* pclose(file); */
  /* free(parts); */
  int status;
  int f = fork();
  if (!f) {
    int pipe_fd[2];
    pipe(pipe_fd);
    int f2 = fork();
    if (!f2) {
      dup2(pipe_fd[1], 1);
      close(pipe_fd[0]);
      char **args = split_string(parts[0], " ");
      execvp(args[0], args);
    } else {
      dup2(pipe_fd[0], 0);
      close(pipe_fd[1]);
      char **args = split_string(parts[1], " ");
      execvp(args[0], args);
    }
  } else {
    wait(&status);
  }
}
