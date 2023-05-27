#include "shell.h"

/**
 * check_interactive – checks if shell is interactive
 * @info: address
 * Return: 1 if interactive, 0 otherwise
 */
int check_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * check_delim - checks if character is a delimiter
 * @c: character to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 otherwise
 */
int check_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * check_alpha - checks for alphabetic character
 * @c: The character check
 * Return: 1 if alpha, 0 otherwise
 */

int check_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * string_to_int - converts string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int string_to_int(char *s)
{
	int i;
	int sign = 1;
	int flag = 0;
	int output;
	unsigned int res = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (s[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}
	output = sign == -1 ? -res : res;
	return (output);
}
