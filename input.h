#ifndef INPUT
#define INPUT
// read line form stdin
char *read_line();
// parses from line
char **parse_args(char *line, const char *to_split);
void count(int *cmds, int *args, char *line);
int exec(char **args);
#endif
