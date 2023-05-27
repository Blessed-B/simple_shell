#include "shell.h"

/**
 * _strncpy - man strncopy
 * @destination: the destination to be copied to
 * @source: string source
 * @n: number of chars to copy
 * Return: the concatenated string
 */
char *_strncpy(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}

	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}

	return (s);
}

/**
 * _strncat - concatenates strings
 * @destination: dest
 * @source: src
 * @n: number of spaces
 * Return: final string
 */
char *_strncat(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;

	while (source[j] != '\0' && j < n)
	{
		destination[i] = source[j];
		i++;
		j++;
	}

	if (j < n)
		destination[i] = '\0';

	return (s);
}

/**
 * _strchr - finds a character in a string
 * @string: string
 * @character: char in search
 * Return: (string) a pointer to the memory area s
 */
char *_strchr(char *string, char character)
{
	do
	{
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}
