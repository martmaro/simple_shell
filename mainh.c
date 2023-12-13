#include "shell.h"

void _prompt(int signal);
int myexecve(char **ag, char **ptr);

/**
 * _prompt - Prints a prompt upon a signal.
 * @sl: The signal.
 */
void _prompt(int sl)
{
	char *print_prompt = "\n$ ";

	(void)sl;
	signal(SIGINT, _prompt);
	write(STDIN_FILENO, print_prompt, 3);
}

/**
 * myexecve - Executes a command in a child process.
 * @ag: An array of arguments.
 * @ptr: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         Otherwise The exit value of the last executed command.
 */
int myexecve(char **ag, char **ptr)
{
	pid_t pid;
	int status, flag = 0, a = 0;
	char *command = ag[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = _locate(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			a = (myerror(ag, 126));
		else
			a = (myerror(ag, 127));
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (pid == 0)
		{
			execve(command, ag, environ);
			if (errno == EACCES)
				r = (myerror(ac, 126));
			_free_env();
			free_memory(ag, ptr);
			free_alias(aliases);
			_exit(r);
		}
		else
		{
			wait(&status);
			a = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (a);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int a = 0, n;
	int *exect = &n;
	char *prompt = "$ ", *new = "\n";

	name = argv[0];
	history_counter = 1;
	aliases = NULL;
	signal(SIGINT, _prompt);

	*exect = 0;
	environ = copy_env();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		a = run_command(argv[1], exect);
		_free_env();
		free_alias(aliases);
		return (*exect);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (a != END_OF_FILE && a != EXIT)
			a = handle_command(exect);
		_free_env();
		free_alias(aliases);
		return (*exect);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		a = handle_command(exect);
		if (a == END_OF_FILE || a == EXIT)
		{
			if (a == END_OF_FILE)
				write(STDOUT_FILENO, new, 1);
			_free_env();
			free_alias(aliases);
			exit(*exect);
		}
	}

	_free_env();
	free_alias(aliases);
	return (*exect);
}
