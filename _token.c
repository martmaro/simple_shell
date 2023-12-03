#include "shell.h"

int _tokenize(char *str, char *delim);
int count_delim(char *str, char *delim);
char **mystrtok(char *line, char *delim);

/**
 * _tokenize - Locates the delimiter index marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to be str.
 */
int _tokenize(char *str, char *delim)
{
	int index = 0, l = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		l++;
		index++;
	}

	return (l);
}

/**
 * count_delim - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int count_delim(char *str, char *delim)
{
	int index, t = 0, l = 0;

	for (index = 0; *(str + index); index++)
		l++;

	for (index = 0; index < l; index++)
	{
		if (*(str + index) != *delim)
		{
			t++;
			index += _tokenize(str + index, delim);
		}
	}

	return (t);
}

/**
 * mystrtok - Tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **mystrtok(char *line, char *delim)
{
	char **p;
	int index = 0, tok, t, letters, l;

	tok = count_delim(line, delim);
	if (tok == 0)
		return (NULL);

	p = malloc(sizeof(char *) * (tok + 2));
	if (!p)
		return (NULL);

	for (t = 0; t < tok; t++)
	{
		while (line[index] == *delim)
			index++;

		letters = _tokenize(line + index, delim);

		p[t] = malloc(sizeof(char) * (letters + 1));
		if (!p[t])
		{
			for (index -= 1; index >= 0; index--)
				free(p[index]);
			free(p);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			p[t][l] = line[index];
			index++;
		}

		p[t][l] = '\0';
	}
	p[t] = NULL;
	p[t + 1] = NULL;

	return (p);
}
