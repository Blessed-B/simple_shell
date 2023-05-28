#include "shell.h"

/**
 * split_string_into_words - splits a string into words. Repeat delimiters are ignored
 * @input_string: the input string
 * @delimiter: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string_into_words(char *input_string, char *delimiter)
{
	int index1, index2, index3, index4, word_count = 0;
	char **string_array;

	if (input_string == NULL || input_string[0] == 0)
		return (NULL);
	if (!delimiter)
		delimiter = " ";
	for (index1 = 0; input_string[index1] != '\0'; index1++)
		if (!check_delim(input_string[index1], delimiter) && (check_delim(input_string[index1 + 1], delimiter) || !input_string[index1 + 1]))
			word_count++;

	if (word_count == 0)
		return (NULL);
	string_array = malloc((1 + word_count) * sizeof(char *));
	if (!string_array)
		return (NULL);
	for (index1 = 0, index2 = 0; index2 < word_count; index2++)
	{
		while (check_delim(input_string[index1], delimiter))
			index1++;
		index3 = 0;
		while (!check_delim(input_string[index1 + index3], delimiter) && input_string[index1 + index3])
			index3++;
		string_array[index2] = malloc((index3 + 1) * sizeof(char));
		if (!string_array[index2])
		{
			for (index3 = 0; index3 < index2; index3++)
				free(string_array[index3]);
			free(string_array);
			return (NULL);
		}
		for (index4 = 0; index4 < index3; index4++)
			string_array[index2][index4] = input_string[index1++];
		string_array[index2][index4] = 0;
	}
	string_array[index2] = NULL;
	return (string_array);
}

/**
 * split_string_into_words2 - splits a string into words
 * @input_string: the input string
 * @delimiter: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string_into_words2(char *input_string, char delimiter)
{
	int index1, index2, index3, index4, word_count = 0;
	char **string_array;

	if (input_string == NULL || input_string[0] == 0)
		return (NULL);
	for (index1 = 0; input_string[index1] != '\0'; index1++)
		if ((input_string[index1] != delimiter && input_string[index1 + 1] == delimiter) ||
			 (input_string[index1] != delimiter && !input_string[index1 + 1]) || input_string[index1 + 1] == delimiter)
			word_count++;
	if (word_count == 0)
		return (NULL);
	string_array = malloc((1 + word_count) * sizeof(char *));
	if (!string_array)
		return (NULL);
	for (index1 = 0, index2 = 0; index2 < word_count; index2++)
	{
		while (input_string[index1] == delimiter && input_string[index1] != delimiter)
			index1++;
		index3 = 0;
		while (input_string[index1 + index3] != delimiter && input_string[index1 + index3] && input_string[index1 + index3] != delimiter)
			index3++;
		string_array[index2] = malloc((index3 + 1) * sizeof(char));
		if (!string_array[index2])
		{
			for (index3 = 0; index3 < index2; index3++)
				free(string_array[index3]);
			free(string_array);
			return (NULL);
		}
		for (index4 = 0; index4 < index3; index4++)
			string_array[index2][index4] = input_string[index1++];
		string_array[index2][index4] = 0;
	}
	string_array[index2] = NULL;
	return (string_array);
}
