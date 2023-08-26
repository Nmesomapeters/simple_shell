#include "shell.h"

char **_copyenv(void);
char **_getenv(const char *var);
void free_env(void);

/**
 * _copyenv - it copies environ
 * Return: new environ
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int number;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (number = 0; environ[number]; number++)
	{
		new_environ[number] = malloc(_strlen(environ[number]) + 1);

		if (!new_environ[number])
		{
			for (number--; number >= 0; number--)
				free(new_environ[number]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[number], environ[number]);
	}
	new_environ[number] = NULL;

	return (new_environ);
}

/**
 * free_env - it frees environ
 */
void free_env(void)
{
	int number;

	for (number = 0; environ[number]; number++)
		free(environ[number]);
	free(environ);
}

/**
 * _getenv - it gets environ v
 * @var: variable
 * Return: NULL or otherwise
 */
char **_getenv(const char *var)
{
	int number, length;

	length = _strlen(var);
	for (number = 0; environ[number]; number++)
	{
		if (_strncmp(var, environ[number], length) == 0)
			return (&environ[number]);
	}

	return (NULL);
}
