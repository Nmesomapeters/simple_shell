#include "shell.h"

char **_strtok(char *line, char *delim);
int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);

/**
 * token_len - it locates the token len
 * @str: The strings
 * @delim: The delimiter
 * Return: delimiter len
 */
int token_len(char *str, char *delim)
{
	int num = 0, length = 0;

	while (*(str + num) && *(str + num) != *delim)
	{
		length++;
		num++;
	}

	return (length);
}

/**
 * count_tokens - it counts tokens
 * @str: The strings
 * @delim: delimiter character
 * Return: The number of words
 */
int count_tokens(char *str, char *delim)
{
	int num, tokens = 0, length = 0;

	for (num = 0; *(str + num); num++)
		length++;

	for (num = 0; num < length; num++)
	{
		if (*(str + num) != *delim)
		{
			tokens++;
			num += token_len(str + num, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - it tokenizes strings
 * @line: line
 * @delim: delimiter character
 * Return: the tokenized words
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int num = 0, tokens, m, letter, n;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (m = 0; m < tokens; m++)
	{
		while (line[num] == *delim)
			num++;

		letter = token_len(line + num, delim);

		ptr[m] = malloc(sizeof(char) * (letter + 1));
		if (!ptr[m])
		{
			for (num -= 1; num >= 0; num--)
				free(ptr[num]);
			free(ptr);
			return (NULL);
		}

		for (n = 0; n < letter; n++)
		{
			ptr[m][n] = line[num];
			num++;
		}

		ptr[m][n] = '\0';
	}
	ptr[m] = NULL;
	ptr[m + 1] = NULL;

	return (ptr);
}
