#include "shell.h"

/**
 * print_string - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void print_string(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		write_char(str[index]);
		index++;
	}
}

/**
 * write_char - writes the character to stderr
 * @c: The character to write
 * Return: On success 1.
 */
int write_char(char c)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}

	if (c != BUF_FLUSH)
		buffer[index++] = c;

	return (1);
}

/**
 * write_char_fd - writes the character c to given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 * Return: On success 1.
 */
int write_char_fd(char c, int fd)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}

	if (c != BUF_FLUSH)
		buffer[index++] = c;

	return (1);
}

/**
 * writes_fd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int writes_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_char_fd(*str++, fd);
	}
	return (i);
}
