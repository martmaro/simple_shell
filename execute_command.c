#include "shell.h"

char *get_command(char *ln, int *exect);
int call_command(char **ag, char **ptr, int *exect);
int execute_command(char **ag, char **ptr, int *exect);
int handle_command(int *exect);
int check_command(char **ag);

/**
 * get_command - Gets a command from standard input.
 * @ln: A buffer to store the command.
 * @exect: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_command(char *ln, int *exect)
{
	size_t n = 0;
	ssize_t r;
	char *prompt = "$ ";

	if (ln)
		free(ln);

	r = mygetln(&ln, &n, STDIN_FILENO);
	if (r == -1)
		return (NULL);
	if (r == 1)
	{
		history_counter++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_command(ln, exect));
	}

	ln[r - 1] = '\0';
	myvariable(&ln, exect);
	_get_ln(&ln, r);

	return (ln);
}

/**
 * call_command - Partitions operators from commands and calls them.
 * @ag: An array of arguments.
 * @ptr: A double pointer to the beginning of ag.
 * @exect: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int call_command(char **ag, char **ptr, int *exect)
{
	int r, index;

	if (!ag[0])
		return (*exect);
	for (index = 0; ag[index]; index++)
	{
		if (mystrncmp(ag[index], "||", 2) == 0)
		{
			free(ag[index]);
			ag[index] = NULL;
			ag = myalias(ag);
			r = execute_command(ag, ptr, exect);
			if (*exect != 0)
			{
				ag = &ag[++index];
				index = 0;
			}
			else
			{
				for (index++; ag[index]; index++)
					free(ag[index]);
				return (r);
			}
		}
		else if (mystrncmp(ag[index], "&&", 2) == 0)
		{
			free(ag[index]);
			ag[index] = NULL;
			ag = myalias(ag);
			r = execute_command(ag, ptr, exect);
			if (*exect == 0)
			{
				ag = &ag[++index];
				index = 0;
			}
			else
			{
				for (index++; ag[index]; index++)
					free(ag[index]);
				return (r);
			}
		}
	}
	ag = myalias(ag);
	r = execute_command(ag, ptr, exect);
	return (r);
}

/**
 * execute_command - Calls the execution of a command.
 * @ag: An array of arguments.
 * @ptr: A double pointer to the beginning of args.
 * @exect: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int execute_command(char **ag, char **ptr, int *exect)
{
	int r, i;
	int (*builtin)(char **ag, char **ptr);

	builtin = _builtin(ag[0]);

	if (builtin)
	{
		r = builtin(ag + 1, ptr);
		if (r != EXIT)
			*exect = r;
	}
	else
	{
		*exect = myexecve(ag, ptr);
		r = *exect;
	}

	history_counter++;

	for (i = 0; ag[i]; i++)
		free(ag[i]);

	return (r);
}

/**
 * handle_command - Gets, calls, and runs the execution of a command.
 * @exect: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_command(int *exect)
{
	int r = 0, index;
	char **ag, *ln = NULL, **ptr;

	ln = get_command(ln, exect);
	if (!ln)
		return (END_OF_FILE);

	ag = mystrtok(ln, " ");
	free(ln);
	if (!ag)
		return (r);
	if (check_command(ag) != 0)
	{
		*exect = 2;
		free_memory(ag, ag);
		return (*exect);
	}
	ptr = ag;

	for (index = 0; ag[index]; index++)
	{
		if (mystrncmp(ag[index], ";", 1) == 0)
		{
			free(ag[index]);
			ag[index] = NULL;
			r = call_command(ag, ptr, exect);
			ag = &ag[++index];
			index = 0;
		}
	}
	if (ag)
		r = call_command(ag, ptr, exect);

	free(ptr);
	return (r);
}

/**
 * check_command - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @ag: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_command(char **ag)
{
	size_t i;
	char *c, *n;

	for (i = 0; ag[i]; i++)
	{
		c = ag[i];
		if (c[0] == ';' || c[0] == '&' || c[0] == '|')
		{
			if (i == 0 || c[1] == ';')
				return (myerror(&ag[i], 2));
			n = ag[i + 1];
			if (n && (n[0] == ';' || n[0] == '&' || n[0] == '|'))
				return (myerror(&ag[i + 1], 2));
		}
	}
	return (0);
}
