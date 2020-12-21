# rush
Shell written in C
> By Eisuke Hirota, Amit Prasad, and Karl Hernandez
> TNPG: Team Rush

# Features
- Arbitrary length input.
- `;` will separate blocks of commands.
	- `ls; echo hello` will work as expected.
- Piping using `|`, redirection of stdin and stdout (using `<` and `>` respectively).
	- Limited to 1 redirection within a block of commands.
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

# Features we failed at implementing:
- History file

# Bugs / Report / More Failures / Specifications
- `make run` will cause a `cuserid()` implicit declaration warning, but *not always,* and with *no negative effects*.

# Function Signatures
