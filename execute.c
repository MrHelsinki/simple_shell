#include "shell.h"

/**
 * shell_loop - main shell loop
 * @info: parameter that returns info struct
 * @av: the argument vector from main
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(info_t *info, char **av)
{
	ssize_t r = 0;
	int b = 0;

	while (r != -1 && b != -2)
	{
		info_init(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			b = check_builtin(info);
			if (b == -1)
				cmd_path(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (b == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (b);
}

/**
 * check_builtin - checks builtin commands
 * @info: info sructure
 *
 * Return: not found -1, executed 0, -2 if signals exit, 1 found not exec
 */
int check_builtin(info_t *info)
{
	int i, b = -1;
	builtin_table btable[] = {
		{"exit", builtin_exit},
		{"env", _env},
		{NULL, NULL}
	};

	for (i = 0; btable[i].type; i++)
		if (_strcmp(info->argv[0], btable[i].type) == 0)
		{
			info->line_count++;
			b = btable[i].func(info);
			break;
		}
	return (b);
}

/**
 * cmd_path - finds a command in PATH
 * @info: info structure
 *
 * Return: void
 */
void cmd_path(info_t *info)
{
	char *path = NULL;
	int i, m;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, m = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			m++;
	if (!m)
		return;

	path = get_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_exec(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_exec(info, info->argv[0]))
			fork_exec(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - creates process to execute using execve
 * @info: info structure
 *
 * Return: void
 */
void fork_exec(info_t *info)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
