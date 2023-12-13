#include "shell.h"

char *permission_denied(char **ag);
char *command_not_found(char **ag);

/**
 * permission_denied - Creates an error message for permission denied failures.
 * @ag: An array of arguments passed to the command.
 * Return: The error string.
 */
char *permission_denied(char **ag)
{
	char *e, *history_str;
	int l;

	history_str = myitoa(history_counter);
	if (!history_str)
		return (NULL);

	l = mystrlen(name) + mystrlen(history_str) + mystrlen(ag[0]) + 24;
	e = malloc(sizeof(char) * (l + 1));
	if (!e)
	{
		free(history_str);
		return (NULL);
	}

	mystrcpy(e, name);
	mystrcat(e, ": ");
	mystrcat(e, history_str);
	mystrcat(e, ": ");
	mystrcat(e, ag[0]);
	mystrcat(e, ": Permission denied\n");

	free(history_str);
	return (e);
}

/**
 * command_not_found - Creates an error message for command not found failures.
 * @ag: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *command_not_found(char **ag)
{
	char *e, *history_str;
	int l;

	history_str = myitoa(history_counter);
	if (!history_str)
		return (NULL);

	l = mystrlen(name) + mystrlen(history_str) + mystrlen(ag[0]) + 16;
	e = malloc(sizeof(char) * (l + 1));
	if (!e)
	{
		free(history_str);
		return (NULL);
	}

	mystrcpy(e, name);
	mystrcat(e, ": ");
	mystrcat(e, history_str);
	mystrcat(e, ": ");
	mystrcat(e, ag[0]);
	mystrcat(e, ": not found\n");

	free(history_str);
	return (e);
}
