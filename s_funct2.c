#include "shell.h"

int _strncmp(const char *s1, const char *s2, size_t n);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);

/**
 * _strchr - Locates a character of strings
 * @s: strings
 * @c: characters
 * Return: returns if c is found or NULL
 */
char *_strchr(char *s, char c)
{
	int num;

	for (num = 0; s[num]; num++)
	{
		if (s[num] == c)
			return (s + num);
	}

	return (NULL);
}

/**
 * _strspn - it gets the of prefix substring.
 * @s: strings
 * @accept: it accepts
 * Return: The number of bytes in s
 */
int _strspn(char *s, char *accept)
{
	int byte = 0;
	int num;

	while (*s)
	{
		for (num = 0; accept[num]; num++)
		{
			if (*s == accept[num])
			{
				byte++;
				break;
			}
		}
		s++;
	}
	return (byte);
}

/**
 * _strcmp - it compares strings
 * @s1: first string
 * @s2: second string
 * Return: Positive bytes or negative bytes
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - it compares two strings
 * @s1: first num
 * @s2: second num
 * @n: number
 * Return: Less than 0
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
