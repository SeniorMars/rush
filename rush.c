#include "rush.h"
#include "input.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    while (1)
    {
        prompt();
        char *line = read_line();
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