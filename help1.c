#include "shell.h"

char *get_pid(void);
char *get_env_value(char *beginning, int len);
void free_args(char **args, char **front);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - it frees agruement
 * @args: arguement
 * @front: front
 */
void free_args(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * get_pid - it gets process id
 * Description: description
 * Return: present pid or otherwise
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - gets environ value
 * @beginning: beginning
 * @len: length
 * Return: a variale or otherwise
 * Description: variables desceiption
 */
char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - it replaces varibales
 * @line: lines
 * @exe_ret: last executed command
 * Description: des
 */
void variable_replacement(char **line, int *exe_ret)
{
	int m, n = 0, length;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (m = 0; old_line[m]; m++)
	{
		if (old_line[m] == '$' && old_line[m + 1] &&
				old_line[m + 1] != ' ')
		{
			if (old_line[m + 1] == '$')
			{
				replacement = get_pid();
				n = m + 2;
			}
			else if (old_line[m + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				n = m + 2;
			}
			else if (old_line[m + 1])
			{
				for (n = m + 1; old_line[n] &&
						old_line[n] != '$' &&
						old_line[n] != ' '; m++)
					;
				length = n - (m + 1);
				replacement = get_env_value(&old_line[m + 1], len);
			}
			new_line = malloc(m + _strlen(replacement)
					  + _strlen(&old_line[n]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, m);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[n]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			m = -1;
		}
	}
}
