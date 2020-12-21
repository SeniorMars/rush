#ifndef UTILS_H
#define UTILS_H
//Trim a string's excess whitespace.
char *trim(char *string);
//Expands any ~ to the home directory into char* dest
char *expand_tilde(char *str, char* home);
// Formats the prompt.
int prompt();
// count instances of character(s) in string
int count_characters(char* str, const char* to_split);
//
void count_commands(int *cmds, int *args, char *line);

int exec_callback(char** args, void (*callback)());
int exec(char **args);

void redir_out(char **parts, char **args);
void redir_in(char **parts, char **args);
#endif