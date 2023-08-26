#include "shell.h"

int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int check_args(char **args);

/**
 * get_args - Gets arguments
 * @line: line
 * @exe_ret: executed command
 * Return: null or otherwise
 */
char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_args - calls argument
 * @args: arguments.
 * @front: front
 * @exe_ret: last executed command
 * Return: executed command
 */
int call_args(char **args, char **front, int *exe_ret)
{
	int retval, num;

	if (!args[0])
		return (*exe_ret);
	for (num = 0; args[num]; num++)
	{
		if (_strncmp(args[num], "||", 2) == 0)
		{
			free(args[num]);
			args[num] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++num];
				num = 0;
			}
			else
			{
				for (num++; args[num]; num++)
					free(args[num]);
				return (retval);
			}
		}
		else if (_strncmp(args[num], "&&", 2) == 0)
		{
			free(args[num]);
			args[num] = NULL;
			args = replace_aliases(args);
			retval = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++num];
				num = 0;
			}
			else
			{
				for (num++; args[num]; num++)
					free(args[num]);
				return (retval);
			}
		}
	}
	args = replace_aliases(args);
	retval = run_args(args, front, exe_ret);
	return (retval);
}

/**
 * run_args - runs arguement
 * @args: arguments
 * @front: front
 * @exe_ret:  last executed command
 * Return: executed command
 */
int run_args(char **args, char **front, int *exe_ret)
{
	int retval, n;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		retval = builtin(args + 1, front);
		if (retval != EXIT)
			*exe_ret = retval;
	}
	else
	{
		*exe_ret = execute(args, front);
		retval = *exe_ret;
	}

	hist++;

	for (n = 0; args[n]; n++)
		free(args[n]);

	return (retval);
}

/**
 * handle_args - handles arguement
 * @exe_ret: last executed command
 * Return:  END_OF_FILE (-2) or otherwise
 */
int handle_args(int *exe_ret)
{
	int retval = 0, num;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (retval);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (num = 0; args[num]; num++)
	{
		if (_strncmp(args[num], ";", 1) == 0)
		{
			free(args[num]);
			args[num] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++num];
			num = 0;
		}
	}
	if (args)
		retval = call_args(args, front, exe_ret);

	free(front);
	return (retval);
}

/**
 * check_args - Checks arguement
 * @args: argument
 * Return: 0 or ohterwise
 */
int check_args(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}
