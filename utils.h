#ifndef UTILS_H
#define UTILS_H
//Trim a string's excess whitespace.
char *trim(char *string);
// Formats the prompt.
int prompt();
// count instances of character(s) in string
int count_characters(char* str, const char* to_split);
//
void count_commands(int *cmds, int *args, char *line);
int exec_callback(char** args, void (*callback)());
int exec(char **args);
void redir(char **parts, char **args);
#endif