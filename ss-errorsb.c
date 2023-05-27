#include "shell.h"

/**
 * convert_string_to_int - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int convert_string_to_int(char *s)
{
	int index = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (index = 0; s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			result *= 10;
			result += (s[index] - '0');

			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (result);
}

/**
 * print_err - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing error type
 * Return: Nothing
 */
void print_err(info_t *info, char *estr)
{
	print_string(info->fname);
	print_string(": ");
	print_int(info->line_count, STDERR_FILENO);
	print_string(": ");
	print_string(info->argv[0]);
	print_string(": ");
	print_string(estr);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int input, int fd)
{
	int (*write_char)(char) = write_char;
	int index, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		write_char = write_char_stderr;

	if (input < 0)
	{
		absolute_value = -input;
		write_char('-');
		count++;
	}
	else
		absolute_value = input;

	current = absolute_value;

	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absolute_value / index)
		{
			write_char('0' + current / index);
			count++;
		}
		current %= index;
	}

	_putchar('0' + current);
	count++;

	return (count);
}

/**
 * _itoa - clone of itoa
 * @number: number to be converted
 * @base: base to convert to
 * @flags: argument flags
 *
 * Return: string representation of the converted number
 */
char *_itoa(long int number, int base, int flags)
{
	static char *digits;
	static char buffer[50];
	char sign = 0;
	char *pointer;
	unsigned long n = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';
	}

	digits = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do
	{
		*--pointer = digits[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--pointer = sign;

	return (pointer);
}

/**
 * com_void - replaces first instance of '#' with '\0'
 * @buffer: string address to mod
 * Return: Always 0
 */
void com_void(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}
