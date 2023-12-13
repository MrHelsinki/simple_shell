#include "shell.h"

/**
 * info_init - initializes info_t struct
 * @info: info structure
 *
 * Return: void
 */
void info_init(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: info structure
 * @av: arg vector
 *
 * Return: void
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
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
/*
		replace_alias(info);
		replace_vars(info);
*/
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 *
 * Return: void
 */
void free_info(info_t *info, int n)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (n)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		ffree(info->environ);
			info->environ = NULL;
		set_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * _strchr - locates a character in a string
 * @str: the string to be parsed
 * @c: the character to look for
 *
 * Return: pointer to memory
 */
char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
