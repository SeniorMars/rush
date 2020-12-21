#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <linux/limits.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>

//Colors
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

char *trim(char *string)
{
    char *end = string + strlen(string);
    while (isspace(*string))
        string++;
    while (isspace(*--end))
        ;
    *(end + 1) = '\0';
    return string;
}

// prompt for our program
int prompt()
{
    char user[PATH_MAX + 1];
    char host[PATH_MAX + 1];
    char cwd[PATH_MAX + 1];
    if (cuserid(user) != '\0')
    {
        printf(YEL "%s", user);
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
        perror("gethostname error");
        return 1;
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf(CYN "%s" RESET "$ ", cwd);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }
    return 0;
}

void count_commands(int *cmds, int *args, char *line)
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
int count_characters(char *str, const char *to_split)
{
    int count = 0;
    for (int i = 0; i < (int)strlen(str); ++i)
    {
        if (str[i] == *to_split)
            ++count;
    }
    return count;
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

int exec_callback(char **args, void (*callback)())
{
    int rc = exec(args);
    (*callback)();
    return rc;
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
    printf("%d\n", fd1);
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