#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/limits.h>
#include <ctype.h>
#include <unistd.h>

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
int count_characters(char *str, const char *to_count)
{
    int count = 0;
    for (int i = 0; i < (int)strlen(str); ++i)
    {
        if (str[i] == *to_count)
            ++count;
    }
    return count;
}