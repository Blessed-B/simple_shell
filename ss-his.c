#include "shell.h"

/**
 * retrieve_history_file - gets the history file
 * @info: parameter structure
 *
 * Return: allocated string containing history file
 */
char *retrieve_history_file(info_t *info)
{
	char *buffer, *home_directory;

	home_directory = get_environment_variable(info, "HOME=");
	if (!home_directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (string_length(home_directory) + string_length(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	string_copy(buffer, home_directory);
	string_concat(buffer, "/");
	string_concat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * save_history - creates a file or appends to an existing file
 * @info: parameter structure
 * Return: 1 on success, else -1
 */
int save_history(info_t *info)
{
	ssize_t file_descriptor;
	char *file_name = retrieve_history_file(info);
	list_t *node = NULL;

	if (!file_name)
		return (-1);

	file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (file_descriptor == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		put_string_to_file_descriptor(node->string, file_descriptor);
		put_character_to_file_descriptor('\n', file_descriptor);
	}
	put_character_to_file_descriptor(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * load_history - reads history from file
 * @info: parameter structure
 *
 * Return: history_count on success, 0 otherwise
 */
int load_history(info_t *info)
{
	int i, last_index = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat st;
	char *buffer = NULL, *file_name = retrieve_history_file(info);

	if (!file_name)
		return (0);

	file_descriptor = open(file_name, O_RDONLY);
	free(file_name);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			add_entry_to_history_list(info, buffer + last_index, line_count++);
			last_index = i + 1;
		}
	if (last_index != i)
		add_entry_to_history_list(info, buffer + last_index, line_count++);
	free(buffer);
	info->history_count = line_count;
	while (info->history_count-- >= HIST_MAX)
		remove_current_node(&(info->history), 0);
	renhis(info);
	return (info->history_count);
}

/**
 * add_entry_to_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @line_count: the history line count
 *
 * Return: Always 0
 */
int add_entry_to_history_list(info_t *info, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_to_end(&node, buffer, line_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renhis- re-numbers history
 * @info: struct
 * Return: the new history count
 */
int renhis(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next;
	}
	return (info->history_count = i);
}
