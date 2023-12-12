#include "shell.h"

int _filenexist(char *file_path);
int run_command(char *file_path, int *exect);

/**
 * _filenexist - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 1.
 */

int _filenexist(char *file_path)
{
	char *e, *history_str;
	int l;

	history_str = myitoa(history_counter);
	if (!history_str)
		return (1);

	l = mystrlen(name) + mystrlen(history_str) + mystrlen(file_path) + 16;
	e = malloc(sizeof(char) * (l + 1));
	if (!e)
	{
		free(history_str);
		return (1);
	}

	mystrcpy(e, name);
	mystrcat(e, ": ");
	mystrcat(e, history_str);
	mystrcat(e, ": Can't open ");
	mystrcat(e, file_path);
	mystrcat(e, "\n");

	free(history_str);
	write(STDERR_FILENO, e, l);
	free(e);
	return (1);
}

/**
 * run_command - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exect: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int run_command(char *file_path, int *exect)
{
	ssize_t file, b_read, i;
	unsigned int size = 0;
	unsigned int old = 120;
	char *line, **ac, **ptr;
	char buffer[120];
	int r;

	history_counter = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exect = _filenexist(file_path);
		return (*exect);
	}
	line = malloc(sizeof(char) * old);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && size == 0)
			return (*exect);
		buffer[b_read] = '\0';
		size += b_read;
		line = myrealloc(line, old, size);
		mystrcat(line, buffer);
		old = size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	myvariable(&line, exect);
	_get_line(&line, size);
	ac = mystrtok(line, " ");
	free(line);
	if (!ac)
		return (0);
	if (check_command(ac) != 0)
	{
		*exect = 2;
		free_memory(ac, ac);
		return (*exect);
	}
	ptr = ac;

	for (i = 0; ac[i]; i++)
	{
		if (mystrncmp(ac[i], ";", 1) == 0)
		{
			free(ac[i]);
			ac[i] = NULL;
			r = call_command(ac, ptr, exect);
			ac = &ac[++i];
			i = 0;
		}
	}

	r = call_command(ac, ptr, exect);

	free(ptr);
	return (r);
}


