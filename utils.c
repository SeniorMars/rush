#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/limits.h>
#include <ctype.h>
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