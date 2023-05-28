#include "shell.h"

/**
 * get_environment - finds string copy of the environment
 * @info: struct with potential args
 * Return: Always 0
 */
char **get_environment(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = linkd_li_to_str(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_environment - Remove an environment variable
 * @info: struct with potential args
 * @variable: the string env var property
 *
 * Return: 1 on delete, 0 otherwise
 */
int unset_environment(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = starts_with_string(node->str, variable);
		if (p && *p == '=')
		{
			info->env_changed = remove_current_node(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}

	return (info->env_changed);
}

/**
 * set_environment - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @variable: the string env var property
 * @value: the string env var value
 *
 * Return: Always 0
 */
int set_environment(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buffer = malloc(string_length(variable) + string_length(value) + 2);
	if (!buffer)
		return (1);

	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);

	node = info->env;
	while (node)
	{
		p = starts_with_string(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_node_to_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;

	return (0);
}