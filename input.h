#ifndef INPUT
#define INPUT
// read line form stdin
char *read_line();
// parses from line
char **parse_args(char *line, const char *to_split);
// makes the prompt to something like this \w >>
int prompt();
void count(int *cmds, int *args, char *line);
void exec(char **args);
#endif
