#include "shell.h"

void *myrealloc(void *ptr, unsigned int old_size, unsigned int new_size);
void _lineptr(char **lineptr, size_t *ptr_size,
		char *buffer, size_t buffer_size);
ssize_t mygetline(char **lineptr, size_t *ptr_size, FILE *fd);

/**
 * myrealloc - allocates a memory block using malloc and free.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size in bytes of the allocated space for ptr.
 * @new_size: size in bytes for the new memory block.
 *
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the allocated memory block.
 */
void *myrealloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *m;
	char *copy, *f;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		m = malloc(new_size);
		if (m == NULL)
			return (NULL);

		return (m);
	}

	if (new_size == 0 && pointr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	copy = ptr;
	m = malloc(sizeof(*copy) * new_size);
	if (m == NULL)
	{
		free(ptr);
		return (NULL);
	}

	f = m;

	for (index = 0; index < old_size && index < new_size; index++)
		f[index] = *copy++;

	free(ptr);
	return (m);
}

/**
 * _lineptr - Reassigns the lineptr variable for mygetline.
 * @lineptr: A buffer to store an input string.
 * @ptr_size: The size of lineptr.
 * @buffer: The string to assign to lineptr.
 * @buffer_size: The size of buffer.
 */
void _lineptr(char **lineptr, size_t *ptr_size,
		char *buffer, size_t buffer_size)
{
	if (*lineptr == NULL)
	{
		if (buffer_size > 120)
			*ptr_size = buffer_size;
		else
			*ptr_size = 120;
		*lineptr = buffer;
	}
	else if (*ptr_size < buffer_size)
	{
		if (buffer_size > 120)
			*ptr_size = buffer_size;
		else
			*ptr_size = 120;
		*lineptr = buffer;
	}
	else
	{
		mystrcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * mygetline - Reads input from a stream.
 * @lineptr: A buffer to store the input.
 * @ptr_size: The size of lineptr.
 * @fd: The stream to read from.
 * Return: The number of bytes read.
 */
ssize_t mygetline(char **lineptr, size_t *ptr_size, FILE *fd)
{
	static ssize_t input;
	ssize_t r;
	char c = 'x', *buffer;
	int i;

	if (input == 0)
		fflush(fd);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		i = read(STDIN_FILENO, &c, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = myrealloc(buffer, input, input + 1);
		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';
	_lineptr(lineptr, ptr_size, buffer, input);
	r = input;
	if (i != 0)
		input = 0;
	return (r);
}


