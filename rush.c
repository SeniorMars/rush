#include "rush.h"
#include "input.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <linux/limits.h>

char last_working_dir[PATH_MAX + 1];

int main()
{
    char *home = getenv("HOME");
    getcwd(last_working_dir, sizeof(last_working_dir));
    while (1)
    {
        //The user@machine, etc.
        prompt();
        char *line = read_line();
        if (strlen(line) > 0)
        {
            //List of commands, separated by ;
            char **cmds = parse_args(line, ";");
            char **p = cmds;
            for (char *command = *p; command; command = *++p)
            {
                char **args = parse_args(command, " ");
                //Count number of args
                int arglen = 0;
                char **p2 = args;
                for (char* c = *p2; c; c = *++p2)
                {
                    ++arglen;
                }
                //Builtin exit function
                if (strcmp(args[0], "exit") == 0)
                {
                    printf("exiting...\n");
                    free(line);
                    free(args);
                    free(cmds);
                    goto end;
                }
                //Builtin cd function
                else if (strcmp(args[0], "cd") == 0)
                {
                    char temp[PATH_MAX + 1];
                    getcwd(temp, sizeof(temp));
                    int rc;
                    //If the command is run with only "cd"
                    if (arglen < 2)
                    {
                        rc = chdir(home);
                    }
                    else
                    {
                        //Handle cd to last directory
                        char *target_dir = args[1];
                        if (strcmp(target_dir, "-") == 0)
                        {
                            rc = chdir(last_working_dir);
                        }
                        else
                        {
                            rc = chdir(target_dir);
                        }
                    }
                    if (rc == -1)
                    {
                        printf("Error: %s\n", strerror(errno));
                    }
                    else
                    {
                        strcpy(last_working_dir, temp);
                    }
                }
                else
                {
                    exec(args);
                }
                free(args);
            }
            free(cmds);
        }
        free(line);
    }
end:
    return 0;
}