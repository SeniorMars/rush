#ifndef INPUT
#define INPUT
// read line form stdin
char *read_line();
// parses from line
char **parse_args(char *line, const char *to_split);
#endif
