
#include "shell.h"

/**
 * string_length - finds string length
 * @string: string to check length
 * Return: integer length of string
 */
int string_length(char *string)
{
	int length = 0;

	if (!string)
		return (0);

	while (*string++)
		length++;
	return (length);
}

/**
 * string_compare - compares two strings
 * @string1: the first string
 * @string2: the second string
 * Return: negative if string1 < string2, positive if string1 > string2, zero if string1 == string2
 */
int string_compare(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}

	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * starts_with_string - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with_string(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * concatenate_strings - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *concatenate_strings(char *destination, char *source)
{
	char *return_value = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (return_value);
}
