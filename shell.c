#include "shell.h"

/**
 * main_shell_loop - shell loop
 * @param_return_info: the parameter & return info struct
 * @arg_vector: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int main_shell_loop(param_return_info_t *param_return_info, char **arg_vector)
{
	ssize_t read = 0;
	int builtin_return = 0;

	while (read != -1 && builtin_return != -2)
	{
		innit_info(param_return_info);
		if (check_interactive(param_return_info))
			_puts("$");
		write_char(BUF_FLUSH);
		read = fetch_inp(param_return_info);
		if (read != -1)
		{
			set_struct_info(param_return_info, arg_vector);
			builtin_return = find_builtin_command(param_return_info);
			if (builtin_return == -1)
				find_command(param_return_info);
		}
		else if (check_interactive(param_return_info))
			_putchar('\n');
		free_struct_info(param_return_info, 0);
	}
	save_history(param_return_info);
	free_struct_info(param_return_info, 1);
	if (!check_interactive(param_return_info) && param_return_info->status)
		exit(param_return_info->status);
	if (builtin_return == -2)
	{
		if (param_return_info->err_num == -1)
			exit(param_return_info->status);
		exit(param_return_info->err_num);
	}
	return (builtin_return);
}

/**
 * find_builtin_command - finds a builtin command
 * @param_return_info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin_command(param_return_info_t *param_return_info)
{
	int i, built_in_ret = -1;
	builtin_table_t builtin_table[] = {
		 {"exit", _exit},
		 {"env", display_env},
		 {"help", cd_helper},
		 {"history", display_history},
		 {"setenv", set_env},
		 {"unsetenv", unset_env},
		 {"cd", _cd},
		 {"alias", my_alias},
		 {NULL, NULL}};

	for (i = 0; builtin_table[i].type; i++)
		if (_strcmp(param_return_info->argv[0], builtin_table[i].type) == 0)
		{
			param_return_info->line_count++;
			built_in_ret = builtin_table[i].func(param_return_info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_command - finds a command in PATH
 * @param_return_info: the parameter & return info struct
 *
 * Return: void
 */
void find_command(param_return_info_t *param_return_info)
{
	char *path = NULL;
	int i, k;
	param_return_info->path = param_return_info->argv[0];
	if (param_return_info->linecount_flag == 1)
	{
		param_return_info->line_count++;
		param_return_info->linecount_flag = 0;
	}
	for (i = 0, k = 0; param_return_info->arg[i]; i++)
		if (!is_delim(param_return_info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = find_command_path(
		 param_return_info,
		 get_env(param_return_info, "PATH="),
		 param_return_info->argv[0]);
	if (path)
	{
		param_return_info->path = path;
		fork_command(param_return_info);
	}
	else
	{
		if ((check_interactive(param_return_info) || get_env(param_return_info, "PATH=") || param_return_info->argv[0][0] == '/') && is_executable_command(param_return_info, param_return_info->argv[0]))
			fork_command(param_return_info);
		else if (*(param_return_info->arg) != '\n')
		{
			param_return_info->status = 127;
			print_err(param_return_info, "not found\n");
		}
	}
}

/**
 * fork_command - forks a an exec thread to run cmd
 * @param_return_info: the parameter & return info struct
 *
 * Return: void
 */
void fork_command(param_return_info_t *param_return_info)
{
	pid_t child_pid;
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(param_return_info->path, param_return_info->argv, get_environment(param_return_info)) == -1)
		{
			free_struct_info(param_return_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(param_return_info->status));
		if (WIFEXITED(param_return_info->status))
		{
			param_return_info->status = WEXITSTATUS(param_return_info->status);
			if (param_return_info->status == 126)
				print_err(param_return_info, "Permission denied\n");
		}
	}
}
