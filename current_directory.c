#include "shell.h"
int (*_builtin(char *command))(char **ag, char **ptr);
int myexit(char **ag, char **ptr);
int mycd(char **ag, char __attribute__((__unused__)) **ptr);
int _help(char **ag, char __attribute__((__unused__)) **ptr);

/**
 * _builtin - Matches a command with a corresponding
 * @command: The command to match.
 * Return: A function pointer to the corresponding builtin.
 */
int (*_builtin(char *command))(char **ag, char **ptr)
{
	builtin_t funcs[] = {
		{ "exit", myexit },
		{ "env", myenv },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", mycd },
		{ "alias", _alias },
		{ "help", _help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (mystrcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * myexit - Causes normal process termination of hell
 * @ag: An array of arguments containing the exit value.
 * @ptr: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 */
int myexit(char **ag, char **ptr)
{
	int i, l = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (ag[0])
	{
		if (ag[0][0] == '+')
		{
			i = 1;
			l++;
		}
		for (; ag[0][i]; i++)
		{
			if (i <= l && ag[0][i] >= '0' && ag[0][i] <= '9')
				num = (num * 10) + (ag[0][i] - '0');
			else
				return (myerror(--ag, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (myerror(--ag, 2));
	ag -= 1;
	free_memory(ag, ptr);
	_free_env();
	free_alias(aliases);
	exit(num);
}

/**
 * mycd - Changes the current directory of the shell process.
 * @ag: An array of arguments.
 * @ptr: A double pointer to the beginning of args.
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int mycd(char **ag, char __attribute__((__unused__)) **ptr)
{
	char **info, *new = "\n";
	char *old_pwd = NULL, *pwd = NULL;
	struct stat dir;

	old_pwd = getcwd(old_pwd, 0);
	if (!old_pwd)
		return (-1);

	if (ag[0])
	{
		if (*(ag[0]) == '-' || mystrcmp(ag[0], "--") == 0)
		{
			if ((ag[0][1] == '-' && ag[0][2] == '\0') ||
					ag[0][1] == '\0')
			{
				if (get_env("OLDPWD") != NULL)
					(chdir(*get_env("OLDPWD") + 7));
			}
			else
			{
				free(old_pwd);
				return (myerror(ag, 2));
			}
		}
		else
		{
			if (stat(ag[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(ag[0]);
			else
			{
				free(old_pwd);
				return (myerror(ag, 2));
			}
		}
	}
	else
	{
		if (get_env("HOME") != NULL)
			chdir(*(get_env("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	info = malloc(sizeof(char *) * 2);
	if (!info)
		return (-1);

	info[0] = "OLDPWD";
	info[1] = old_pwd;
	if (_setenv(info, info) == -1)
		return (-1);

	info[0] = "PWD";
	info[1] = pwd;
	if (_setenv(info, info) == -1)
		return (-1);
	if (ag[0] && ag[0][0] == '-' && ag[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, mystrlen(pwd));
		write(STDOUT_FILENO, new, 1);
	}
	free(old_pwd);
	free(pwd);
	free(info);
	return (0);
}

/**
 * _help - Displays information about shell builtin commands.
 * @ag: An array of arguments.
 * @ptr: A pointer to the beginning of args
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int _help(char **ag, char __attribute__((__unused__)) **ptr)
{
	if (!ag[0])
		print_builtin();
	else if (mystrcmp(ag[0], "alias") == 0)
		print_alias();
	else if (mystrcmp(ag[0], "cd") == 0)
		print_cd();
	else if (mystrcmp(ag[0], "exit") == 0)
		print_exit();
	else if (mystrcmp(ag[0], "env") == 0)
		print_env();
	else if (mystrcmp(ag[0], "setenv") == 0)
		print_setenv();
	else if (mystrcmp(ag[0], "unsetenv") == 0)
		print_unsetenv();
	else if (mystrcmp(ag[0], "help") == 0)
		print_help();
	else
		write(STDERR_FILENO, name, mystrlen(name));

	return (0);
