#include "shell.h"

/**
 * is_chain_delimiter - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain_delimiter(info_t *info, char *buffer, size_t *position)
{
	size_t index = *position;

	if (buffer[index] == '|' && buffer[index + 1] == '|')
	{
		buffer[index] = 0;
		index++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[index] == '&' && buffer[index + 1] == '&')
	{
		buffer[index] = 0;
		index++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[index] == ';') /* found end of this command */
	{
		buffer[index] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*position = index;
	return (1);
}

/**
 * chain_checker – checks if chain should continue
 * @info: struct
 * @buffer: the char buffer
 * @position: address of index
 * @start_position: position at start
 * @length: buffer length
 */

void chain_checker(info_t *info, char *buffer, size_t *position, size_t start_position, size_t length)
{
	size_t index = *position;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[start_position] = 0;
			index = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[start_position] = 0;
			index = length;
		}
	}

	*position = index;
}

/**
 * change_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_alias(info_t *info)
{
	int index;
	list_t *node;
	char *pointer;

	for (index = 0; index < 10; index++)
	{
		node = find_node_with_prefix(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		pointer = _strchr(node->str, '=');
		if (!pointer)
			return (0);
		pointer = _strdup(pointer + 1);
		if (!pointer)
			return (0);
		info->argv[0] = pointer;
	}
	return (1);
}

/**
 * change_variables - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_variables(info_t *info)
{
	int index = 0;
	list_t *node;

	for (index = 0; info->argv[index]; index++)
	{
		if (info->argv[index][0] != '$' || !info->argv[index][1])
			continue;

		if (!string_compare(info->argv[index], "$?"))
		{
			change_string(&(info->argv[index]),
							  _strdup(_itoa(info->status, 10, 0)));
			continue;
		}
		if (!string_compare(info->argv[index], "$$"))
		{
			change_string(&(info->argv[index]),
							  _strdup(_itoa(getpid(), 10, 0)));
			continue;
		}
		node = find_node_with_prefix(info->env, &info->argv[index][1], '=');
		if (node)
		{
			change_string(&(info->argv[index]),
							  _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		change_string(&info->argv[index], _strdup(""));
	}
	return (0);
}

/**
 * change_string – used to replace a string
 * @old_string: old string address
 * @new_string: address of new string
 * Return: 1 if replaced, 0 otherwise
 */
int change_string(char **old_string, char *new_string)
{
	free(*old_string);
	*old_string = new_string;
	return (1);
}
