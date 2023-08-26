#include "shell.h"

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);


/**
 * shellby_env - it dispalys presrnt environ
 * @args: arguemnet
 * @front: front
 * Return: -1 or otherwise
 * Description: describes the code
 */
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int number;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (number = 0; environ[number]; number++)
	{
		write(STDOUT_FILENO, environ[number], _strlen(environ[number]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellby_setenv - it sets environ
 * @front: front
 * @args: arguement
 * Description: desv
 * Return: -1 or otherwise 0
 */
int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int number;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (number = 0; environ[number]; number++)
		new_environ[number] = environ[number];

	free(environ);
	environ = new_environ;
	environ[number] = new_value;
	environ[number + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - it unsets environ
 * @front: front
 * @args: arguement
 * Description: dd
 * Return: -1 or otherwise 0
 */
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int number, number2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(args, -1));

	for (number = 0, number2 = 0; environ[number]; number++)
	{
		if (*env_var == environ[number])
		{
			free(*env_var);
			continue;
		}
		new_environ[number2] = environ[number];
		number2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
