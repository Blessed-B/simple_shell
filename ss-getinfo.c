#include "shell.h"

/**
 * innit_info - initializes info_t struct
 * @info: address
 */
void innit_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_struct_info - initializes info_t
 * @info: address
 * @av: argument vector
 */
void set_struct_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = split_string_into_words(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		change_alias(info);
		change_variables(info);
	}
}

/**
 * free_struct_info - frees info_t
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_struct_info(info_t *info, int all)
{
	free_strings(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_current_list(&(info->env));
		if (info->history)
			free_current_list(&(info->history));
		if (info->alias)
			free_current_list(&(info->alias));
		free_strings(info->environ);
		info->environ = NULL;
		free_pointer((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
