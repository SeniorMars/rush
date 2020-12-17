#ifndef INPUT
#define INPUT
// read line form stdin
char *read_line();
//Left trim
char *trim(char *string);
// parses from line
char **parse_args(char *line, const char *to_split);
// makes the prompt to something like this \w >>
int prompt();
void count(int *cmds, int *args, char *line);
int exec(char **args);
#endif
