#ifndef INPUT
#define INPUT

/* char *read_line()
 * Returns the next line of input from STDIN, length independent.
 * NOTE: This string must be freed to prevent a memory leak.
 * 
 * Parameters: None
 * Returns:
 * char *line -> A reference to a dynamically allocated string.
*/
char *read_line();

/* char **split_string(char *str, char* to_split)
 * Splits a string on every instance of the delimiter in *to_split
 * 
 * Parameters:
 * char *str -> Reference to the string to be split.
 * char *to_split -> The delimiter to split the str by
 * Returns:
 * char **args -> A list of the split strings
*/
char **split_string(char *str, const char *to_split);
#endif
