#ifndef UTILS_H
#define UTILS_H
/* char *trim(char *string)
 * Removes all leading and trailing whitespace from a string.
 * 
 * Parameters:
 * char *string -> The input string.
 * Returns:
 * char *string -> The trimmed string.
*/
char *trim(char *string);

/* char *expand_tilde(char *str, char* home)
 * Expands any ~ in a string to the home directory path specified in char* home.
 * 
 * Parameters:
 * char *str -> The reference string.
 * char *home -> The home directory path.
 * Returns:
 * char *dirstr -> The expanded string.
*/
char *expand_tilde(char *str, char* home);

/* int prompt()
 * Prints the command prompt to STDOUT.
 * NOTE: This string must be freed to prevent a memory leak.
 * 
 * Parameters: None
 * Returns:
 * 0 -> Successful
 * 1 -> Error fetching information.
*/
int prompt();

/* int count_characters(char* str, const char* to_count)
 * Counts the number of *to_count in *str
 * 
 * Parameters:
 * char *str -> The reference string.
 * char *to_count -> The character to count
 * Returns:
 * int count -> The number of instances *to_count appears in *str
*/
int count_characters(char* str, const char* to_count);

/* void count_commands(int *cmds, int *args, char *line
 * Counts the number of commands and arguments in *line, stored in *cmds and *args respectively.
 * 
 * Parameters:
 * int *cmds -> The command counter reference.
 * int *args -> The argument counter reference.
 * char *line -> The line to parse.
*/
void count_commands(int *cmds, int *args, char *line);
#endif