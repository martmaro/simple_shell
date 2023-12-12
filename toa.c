#include "shell.h"

int _number_len(int num);
char *myitoa(int num);
int myerror(char **ac, int error);

/**
 * _number_len - Counts the length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int _number_len(int num)
{
	unsigned int n;
	int l = 1;

	if (num < 0)
	{
		l++;
		n = num * -1;
	}
	else
	{
		n = num;
	}
	while (n > 9)
	{
		l++;
		n /= 10;
	}

	return (l);
}

/**
 * myitoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *myitoa(int num)
{
	char *b;
	int l = _number_len(num);
	unsigned int n;

	b = malloc(sizeof(char) * (l + 1));
	if (!b)
		return (NULL);

	b[l] = '\0';

	if (num < 0)
	{
		n = num * -1;
		b[0] = '-';
	}
	else
	{
		n = num;
	}

	l--;
	do {
		b[l] = (n % 10) + '0';
		n /= 10;
		l--;
	} while (n > 0);

	return (b);
}


/**
 * myerror - Writes a custom error message to stderr.
 * @ac: An array of arguments.
 * @error: The error value.
 *
 * Return: The error value.
 */
int myerror(char **ac, int error)
{
	char *er;

	switch (error)
	{
	case -1:
		er = _env_error(ac);
		break;
	case 1:
		er = _error(ac);
		break;
	case 2:
		if (*(ac[0]) == 'e')
			er = _exit_error(++ac);
		else if (ac[0][0] == ';' || ac[0][0] == '&' || ac[0][0] == '|')
			er = mysyntax(ac);
		else
			er = directory_error(ac);
		break;
	case 126:
		er = permission_denied(ac);
		break;
	case 127:
		er = command_not_found(ac);
		break;
	}
	write(STDERR_FILENO, er, mystrlen(er));

	if (er)
		free(er);
	return (error);

}
