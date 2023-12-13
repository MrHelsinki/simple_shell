#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: info structure
 * @buf: buffer
 * @len: size
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes = 0;
	size_t len_p = 0;

	if (!*len) 
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		bytes = _getline(info, buf, &len_p);
		if (bytes > 0)
		{
			if ((*buf)[bytes - 1] == '\n')
			{
				(*buf)[bytes - 1] = '\0'; 
				bytes--;
			}
			info->linecount_flag = 1;
			*len = bytes;
			info->cmd_buf = buf;
		}
	}
	return (bytes);
}

/**
 * get_input - gets a line
 * @info: info structure
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t len;
	ssize_t bytes = 0;
	char **buf_p = &(info->arg);
	static size_t i, j;
	char *p;
	_putchar(BUF_FLUSH);
	bytes = input_buf(info, &buf, &len);
	if (bytes == -1) 
		return (-1);
	if (len) 
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (chain_str(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; 
		if (i >= len)
		{
			i = len = 0; 
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (bytes);
}

/**
 * read_buf - reads a buffer
 * @info: info structure
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t bytes = 0;

	if (*i)
		return (0);
	bytes = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytes >= 0)
		*i = bytes;
	return (bytes);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t m;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	m = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + m : m + 1);
	if (!new_p) 
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, m - i);
	else
		_strncpy(new_p, buf + i, m - i + 1);

	s += m - i;
	i = m;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}



/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
