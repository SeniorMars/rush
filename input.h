#ifndef INPUT
#define INPUT
// Read line form stdin, returns a pointer to a dynamically sized string.
char *read_line();
// Splits a string on any delimiters present in char *to_split
char **parse_args(char *line, const char *to_split);
#endif
