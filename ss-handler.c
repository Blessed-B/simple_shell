#include "shell.h"

/**
 * is_executable_command - determines if a file is an executable command
 * @info: the info struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable_command(info_t *info, char *file_path)
{
	struct stat st;

	(void)info;
	if (!file_path || stat(file_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_characters - duplicates characters
 * @path_string: the PATH string
 * @start_index: starting index
 * @stop_index: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_characters(char *path_string, int start_index, int stop_index)
{
	static char buffer[1024];
	int index = 0, k = 0;

	for (k = 0, index = start_index; index < stop_index; index++)
		if (path_string[index] != ':')
			buffer[k++] = path_string[index];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_command_path - finds this cmd in the PATH string
 * @info: the info struct
 * @path_string: the PATH string
 * @command: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_command_path(info_t *info, char *path_string, char *command)
{
	int index = 0, current_position = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((string_length(command) > 2) && starts_with_string(command, "./"))
	{
		if (is_executable_command(info, command))
			return (command);
	}
	while (true)
	{
		if (!path_string[index] || path_string[index] == ':')
		{
			path = duplicate_characters(path_string, current_position, index);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_executable_command(info, path))
				return (path);
			if (!path_string[index])
				break;
			current_position = index;
		}
		index++;
	}
	return (NULL);
}
