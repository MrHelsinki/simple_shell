#include "shell.h"

/**
 * is_exec - determines if a file is executable
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_exec(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @path: PATH string
 * @first: starting index
 * @last: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *path, int first, int last)
{
	static char buf[1024];
	int i = 0, n = 0;

	for (n = 0, i = first; i < last; i++)
		if (path[i] != ':')
			buf[n++] = path[i];
	buf[n] = 0;
	return (buf);
}

/**
 * get_path - gets the PATH
 * @info: the info struct
 * @path: PATH string
 * @cmd: the cmd to get path for
 *
 * Return: path of cmd or NULL
 */
char *get_path(info_t *info, char *path, char *cmd)
{
	int i = 0, s = 0;
	char *p;

	if (!path)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_exec(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path[i] || path[i] == ':')
		{
			p = dup_chars(path, s, i);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (is_exec(info, p))
				return (p);
			if (!path[i])
				break;
			s = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * chain_str - check if string is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int chain_str(info_t *info, char *buf, size_t *p)
{
        size_t i = *p;

        if (buf[i] == '|' && buf[i + 1] == '|')
        {
                buf[i] = 0;
                i++;
                info->cmd_buf_type = CMD_OR;
        }
        else if (buf[i] == '&' && buf[i + 1] == '&')
        {
                buf[i] = 0;
                i++;
                info->cmd_buf_type = CMD_AND;
        }
        else if (buf[i] == ';')
        {
                buf[i] = 0;
                info->cmd_buf_type = CMD_CHAIN;
        }
        else
                return (0);
        *p = i;
        return (1);
}

/**
 * check_chain - checks if to continue chaining
 * @info: parameter struct
 * @buf: the buffer
 * @p: current position in buf
 * @i: starting of buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
        size_t j = *p;

        if (info->cmd_buf_type == CMD_AND)
        {
                if (info->status)
                {
                        buf[i] = 0;
                        j = len;
                }
        }
        if (info->cmd_buf_type == CMD_OR)
        {
                if (!info->status)
                {
                        buf[i] = 0;
                        j = len;
                }
        }

        *p = j;
}
