#include "shell.h"

void print_builtin(void);
void print_alias(void);
void print_cd(void);
void print_exit(void);
void print_help(void);

/**
 * print_builtin - Displays all possible builtin shell commands.
 */
void print_builtin(void)
{
	char *message = "\n internal commands.\n";

	write(STDOUT_FILENO, message, mystrlen(message));
	message = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, message, mystrlen(message));
}

/**
 * print_alias - Displays information on the shell builtin command 'alias'.
 */
void print_alias(void)
{
	char *message = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, message, mystrlen(message));
	message = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, message, mystrlen(message));
}

/**
 * print_cd - Displays information on the shell builtin command 'cd'.
 */
void print_cd(void)
{
	char *message = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, message, mystrlen(message));
	message = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "after a change of directory.\n";
	write(STDOUT_FILENO, message, mystrlen(message));
}

/**
 * print_exit - Displays information on the shell builtin command 'exit'.
 */
void print_exit(void)
{
	char *message = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, message, mystrlen(message));
	message = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = " exit 0.\n";
	write(STDOUT_FILENO, message, mystrlen(message));
}

/**
 * print_help - Displays information on the shell builtin command 'help'.
 */
void print_help(void)
{
	char *message = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, message, mystrlen(message));
	message = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, message, mystrlen(message));
	message = "builtin command.\n";
	write(STDOUT_FILENO, message, mystrlen(message));
}
