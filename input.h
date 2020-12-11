#ifndef INPUT
#define INPUT
char* read_line();
char **parse_args(char *line);
void count(int *cmds, int *args, char *line);
#endif
