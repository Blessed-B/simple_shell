#include "shell.h"

/**
 * input_buffer - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of length variable
 * 
 * Return: bytes read
 */
ssize_t input_buffer(info_t *info, char **buffer, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigint_handler);

#if USE_GETLINE
		r = getline(buffer, &len_p, stdin);
#else
		r = custom_getline(info, buffer, &len_p);
#endif

		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}

			info->linecount_flag = 1;
			com_void(*buffer);
			add_entry_to_history_list(info, *buffer, info->histcount++);

			{
				*length = r;
				info->cmd_buf = buffer;
			}
		}
	}

	return (r);
}

/**
 * fetch_inp - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t fetch_inp(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buffer(info, &buf, &len);

	if (r == -1) /* EOF */
		return (-1);

	if (len)
	{
		j = i;
		p = buf + i;

		chain_checker(info, buf, &j, i, len);

		while (j < len)
		{
			if (is_chain_delimiter(info, buf, &j))
				break;

			j++;
		}

		i = j + 1;

		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;				/* pass back pointer to current command position */
		return (string_length(p)); /* return length of current command */
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @index: size
 *
 * Return: r
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *index)
{
	ssize_t r = 0;

	if (*index)
		return (0);

	r = read(info->readfd, buffer, READ_BUF_SIZE);

	if (r >= 0)
		*index = r;

	return (r);
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @pointer: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated pointer buffer if not NULL
 *
 * Return: s
 */
int custom_getline(info_t *info, char **pointer, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *pointer;

	if (p && length)
		s = *length;

	if (i == len)
		i = len = 0;

	r = read_buffer(info, buf, &len);

	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');

	k = c ? 1 + (unsigned int)(c - buf) : len;

	new_p = reallocate_memory(p, s, s ? s + k : k + 1);

	if (!new_p)

		return (p ? free(p), -1 : -1);

	if (s)

		_strncat(new_p, buf + i, k - i);

	else

		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;

	i = k;

	p = new_p;

	if (length)

		*length = s;

	*pointer = p;

	return (s);
}

/**
 * sigint_handler- blocks ctrl-C
 * @sig_num: signal int
 *
 * Return:void
 */
void sigint_handler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
