#include "shell.h"

/**
 * _exit - exits the shell
 * @info: Struct with potential arguments.
 * (0) if info.argv[0] != "exit"
 */
int _exit(info_t *info)
{
	int exit_status;

	if (info->argv[1])
	{
		exit_status = convert_string_to_int(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_err(info, "Illegal number: ");
			print_string(info->argv[1]);
			write_char('\n');
			return (1);
		}
		info->err_num = convert_string_to_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cd - changes the current working directory
 * @info: struct
 * Return: Always 0
 */
int _cd(info_t *info)
{
	char *current_dir;
	char *new_dir;
	char buffer[1024];
	int chdir_return;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
	{
		_puts("TODO:>>getcwd failure emsg here<<\n");
	}
	if (!info->argv[1])
	{
		new_dir = get_env(info, "HOME=");
		if (!new_dir)
		{
			chdir_return = chdir((new_dir = get_env(info, "PWD=")) ? new_dir : "/");
		}
		else
		{
			chdir_return = chdir(new_dir);
		}
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_return = chdir((new_dir = get_env(info, "OLDPWD=")) ? new_dir : "/");
	}
	else
	{
		chdir_return = chdir(info->argv[1]);
	}
	if (chdir_return == -1)
	{
		print_err(info, "can't cd to ");
		print_string(info->argv[1]), write_char('\n');
	}
	else
	{
		set_environment(info, "OLDPWD", get_env(info, "PWD="));
		set_environment(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * cd_helper - changes the current directory of the process
 * @info: struct
 * Return: Always 0
 */
int cd_helper(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

#include "shell.h"

/**
 * display_history - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @info: struct with potential args
 *
 * Return: Always 0
 */
int display_history(info_t *info)
{
	write_linked_list(info->history);
	return (0);
}

/**
 * remove_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *str)
{
	char *p;
	char c;
	int result;

	p = _strchr(str, '=');
	if (!p)
	{
		return (1);
	}
	c = *p;
	*p = 0;
	result = remove_current_node(&(info->alias),
										  retrieve_index(info->alias,
															  find_node_with_prefix(info->alias, str, -1)));
	*p = c;
	return (result);
}

/**
 * _alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
	{
		return (1);
	}
	if (!*++p)
	{
		return (remove_alias(info, str));
	}

	remove_alias(info, str);
	return (add_node_to_end(&(info->alias), str, 0) == NULL);
}

/**
 * display_alias - prints an alias
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */

int display_alias(list_t *node)
{
	char *equal_sign = NULL;
	char *current_char = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (current_char = node->str; current_char <= equal_sign; current_char++)
		{
			_putchar(*current_char);
		}
		_putchar('\'');
		_puts(equal_sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics built-in alias
 * @info: struct with potential args
 * Return: Always 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *equal_sign = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			display_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		equal_sign = _strchr(info->argv[i], '=');
		if (equal_sign)
		{
			_alias(info, info->argv[i]);
		}
		else
		{
			display_alias(find_node_with_prefix(info->alias, info->argv[i], '='));
		}
	}

	return (0);
}
