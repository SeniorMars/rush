#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

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
#endif