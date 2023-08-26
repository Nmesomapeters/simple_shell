#include "shell.h"

char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strlen(const char *s);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - length of a string
 * @s: characters string
 * Return: returns length of the character strings
 */
int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (len);
	for (len = 0; s[len]; len++)
		;
	return (len);
}

/**
 * _strcpy - it copies the string
 * @dest: destination of copied strings
 * @src: src of the source string.
 * Return: dest
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - it concantenates two strings
 * @dest: destination stringe
 * @src: src source strings
 * Return: destination string.
 */
char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - it concantenates two strings
 * @dest: destination strings
 * @src: source strings
 * @n: n bytes to copy from src
 * Return:  destination string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}
