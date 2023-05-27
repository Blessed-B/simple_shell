#include "shell.h"

/**
 * display_env - prints the current environment
 * @info: struct with potential comments.
 * Return: Always 0
 */

int display_env(info_t *info)
{
	write_linked_list_string(info->env);
	return (0);
}

/**
 * get_env - gets the value of an environ variable
 * @info: struct with potential args
 * @name: env var name
 *
 * Return: the value
 */
char *get_env(info_t *info, const char *name)
{
	list_t *current_node = info->env;
	char *value;

	while (current_node)
	{
		value = starts_with_string(current_node->str, name);
		if (value && *value)
		{
			return (value);
		}
		current_node = current_node->next;
	}
	return (NULL);
}

/**
 * set_env - Initialize a new environment variable,
 * or modify an existing one
 * @info: struct with potential args
 *  Return: Always 0
 */

int set_env(info_t *info)
{
	if (info->argc != 3)
	{
		print_string("Incorrect number of arguements\n");
		return (1);
	}
	if (set_environment(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_env - Remove an environment variable
 * @info: struct with potential args
 * Return: Always 0
 */
int unset_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		print_string("Too few arguments.\n");
		return (1);
	}

	for (i = 1; i < info->argc; i++)
	{
		unset_environment(info, info->argv[i]);
	}

	return (0);
}

/**
 * populate_environ_list - populates env linked list
 * @info: struct with potential arguments
 * Return: Always 0
 */
int populate_environ_list(info_t *info)
{
	list_t *current_node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		add_node_to_end(&current_node, environ[i], 0);
	}
	info->env = current_node;
	return (0);
}
