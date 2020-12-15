#ifndef INPUT
#define INPUT
char* read_line();
char **parse_args(char *line);
int prompt();
void count(int *cmds, int *args, char *line);
void exec(char ** args);
#endif
