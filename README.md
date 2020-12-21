# rush
Shell written in C
> By Eisuke Hirota, Amit Prasad, and Karl Hernandez  
> TNPG: Team Rush

# Features
- Arbitrary length input.
- `;` will separate blocks of commands.
	- `ls; echo hello` will work as expected.
- Piping using `|`, redirection of stdin and stdout (using `<` and `>` respectively).
	- Limited to 1 redirection/pipe within a block of commands.
	- `ls > test1 > test2` will only output to `test1`.
	- `ls > test1; echo hello > test2` will work for both `test1`, and `test2`.
- Robust `cd` command.
	- `cd` with no arguments sends you to the home directory.
	- `cd -` will take you back to the previous working directory.
- `~` anywhere in any command will expand to `/home/username`.
	- `cd ~` will navigate to the home directory.
	- `ls ~` will list the contents of the home directory.
- username@hostname:cwd formatted prompt, with color included.
- `<Ctrl-C>` signal handler.
- Exit using `exit` command.

# Features we failed at implementing / Only attempted to implement:
- History file, abandoned since capturing keystrokes as they are pressed was nuanced (setting the tty to raw, etc.)

# Bugs / Report / More Failures / Specifications
- `make run` will cause a `cuserid()` implicit declaration warning, but *not always,* and with *no negative effects*.

# Files & Function Signatures
### rush.c
- Entrypoint into the shell
```c
/* int main()
 * C Entrypoint.
*/
int main();

/* void sighandler(int signo)
 * Handles signal given in signo, currently just SIGINT.
 * Parameters:
 * int signo -> The signal number.
*/
void sighandler(int signo);
```
### input.c
- Contains tools for reading and splitting input.
```c
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
```
### utils.c
- Utility functions for splitting strings, displaying prompts, etc.
```c
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

/* void greet()
 * Prints the greeting to STDOUT.
*/
void greet();

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
```
### commandhandler.c
- Forks and executes commands, handles redirections and piping.
```c
/* void exec(char **args)
 * Forks, and runs the command stored in the **args array.
 * 
 * Parameters:
 * char **args -> The array of strings that represent the command to be run.
*/
void exec(char **args);

/* void exec_callback(char** args, void (*callback)())
 * Wrapper for exec(char** args). Runs the callback void() function in *callback.
 * 
 * Parameters:
 * char **args -> The array of strings that represent the command to be run.
 * void (*callback)() -> a void() function that is run after the exec completes.
*/
void exec_callback(char** args, void (*callback)());

/* redir_out(char **parts, char **args)
 * Redirects the STDOUT of the command stored in **args (and in **parts[0]) to the file specified in **parts[1]
 * 
 * Parameters:
 * char **[arts] -> An array which has the command to be run, followed by the file where STDOUT is redirected to.
 * char **args -> An array which will be passed on to exec_callback
*/
void redir_out(char **parts, char **args);

/* void restore_stdout()
 * Restores STDOUT from a saved stream.
*/
void restore_stdout();

/* redir_in(char **parts, char **args)
 * Redirects the STDIN of the command stored in **args (and in **parts[0]) from a file specified in **parts[1]
 * 
 * Parameters:
 * char **[arts] -> An array which has the command to be run, followed by the file where STDIN is redirected from.
 * char **args -> An array which will be passed on to exec_callback
*/
void redir_in(char **parts, char **args);

/* void restore_stdin()
 * Restores STDIN from a saved stream.
*/
void restore_stdin();

/* void pipe_cmd(char **parts) 
 * Creates a pipe between two commands in **parts
 *
 * Parameters:
 * char **parts -> An array which contains commands separated by pipes
*/
void pipe_cmd(char **parts);
```