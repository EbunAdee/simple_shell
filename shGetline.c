#include "shell.h"

/**
 *input_buf - Read input from the standard input or command chain buffer
 *@info: Pointer to the info_t structure
 *@buf: Pointer to the buffer to store the input
 *@len: Pointer to the length of the buffer
 *
 *This function reads input from the standard input
 * or the command chain buffer.
 *It updates the provided buffer and its length, handles special characters,
 *and maintains command history and chaining.
 *
 *Return: The number of characters read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t read_result = 0;
	size_t allocated_length = 0;

	if (*len == 0)
	{
		/*If the buffer is empty, read input */
		free(*buf); /*Free the existing buffer */
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if USEgetLine
	read_result = getline(buf, &allocated_length, stdin);
#else
	read_result = getLine(info, buf, &allocated_length);
#endif

		if (read_result > 0)
		{ /*Remove trailing newline if present */
			if ((*buf)[read_result - 1] == '\n')
			{	(*buf)[read_result - 1] = '\0';
				read_result--;
			}

			info->linecount_flag = 1;
			removeComm(*buf);
			buildHistoryList(info, *buf, info->histcount++);

			/*Check for command chaining */
			/* if (_strChr(*buf, ';')) */
			{	*len = read_result;
				info->cmd_buf = buf;
			}
		}
	}

	return (read_result);
}

/**
 *getInput - Get input from the user or the command chain buffer
 *@info: Pointer to the info_t structure
 *
 *This function retrieves input from the user or the command chain buffer.
 *It manages command chaining and keeps track of the current command position.
 *
 *Return: The length of the current command or -1 on EOF.
 */
ssize_t getInput(info_t *info)
{
	static char *chain_buffer;
	static size_t chain_buffer_position, current_position, buffer_length;
	ssize_t result = 0;
	char **command_pointer = &(info->arg);
	char *command_start = NULL;

	putChar(BUF_FLUSH);
	result = input_buf(info, &chain_buffer, &buffer_length);
	if (result == -1)
		return (-1);
	if (buffer_length > 0)
	{
		/*There are commands left in the chain buffer */
		chain_buffer_position = current_position;
		command_start = chain_buffer + current_position;
		/*Check for command chain and iterate through commands */
		checkChain(info, chain_buffer, &chain_buffer_position,
									current_position, buffer_length);
		while (chain_buffer_position < buffer_length)
		{
			if (isChain(info, chain_buffer, &chain_buffer_position))
				break;
			chain_buffer_position++;
		}
		current_position = chain_buffer_position + 1; /*Increment nullified ';' */
		if (current_position >= buffer_length)
		{ /*If we've reached the end of the buffer, reset position and length */
			current_position = 0;
			buffer_length = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		/*Pass back a pointer to the current command position */
		*command_pointer = command_start;
		/*Return the length of the current command */
		return (strLen(command_start));
	}
	/*If it's not a command chain, pass back the buffer from getLine() */
	*command_pointer = chain_buffer;
	/*Return the length of the buffer from getLine() */
	return (result);
}

/**
 *read_buf - Read data from a file descriptor into a buffer
 *@info: Pointer to the info_t structure
 *@buf: Pointer to the buffer for data storage
 *@i: Pointer to the current position in the buffer
 *
 *This function reads data from the file descriptor into the provided buffer.
 *It updates the position pointer and the number of bytes read.
 *
 *Return: The number of bytes read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t bytes_read = 0;

	/*Check if there are still bytes to be read in the buffer */
	if (*i > 0)
	{
		return (0);
	}

	/*Read data from the file descriptor into the buffer */
	bytes_read = read(info->readfd, buf, READ_BUF_SIZE);

	if (bytes_read >= 0)
	{
		/*Update the position "i" with the number of bytes read */
		*i = (size_t) bytes_read;
	}

	return (bytes_read);
}

/**
 *getLine - Read a line from the input buffer
 *@info: Pointer to the info_t structure
 *@ptr: Pointer to the buffer to store the line
 *@length: Pointer to the length of the buffer
 *
 *This function reads a line from the input buffer, extending the buffer
 *as needed to accommodate the line. It handles buffer reallocation and
 *maintains the buffer length and position.
 *
 *Return: The length of the read line or -1 on error.
 */
int getLine(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i = 0, len;
	char *p = *ptr, *new_p = NULL, *c = NULL;
	ssize_t r = 0;
	size_t k;

	if (i == len)
	{
		i = len = 0;
		r = read_buf(info, buf, &len);

		if (r == -1 || (r == 0 && len == 0))
			return (-1);
	}

	c = _strChr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;

	new_p = reAlloc(p, *length, *length ? *length + k : k + 1);

	if (!new_p)
	{
		if (p)
			free(p);
		return (-1);
	}

	if (*length)
		_strnCat(new_p, buf + i, k - i);
	else
		_strnCpy(new_p, buf + i, k - i + 1);

	*length += k - i;
	i = k;
	*ptr = new_p;

	return (*length);
}

/**
 *sigintHandler - Handle the SIGINT signal
 *@sig_num: The signal number (unused in this function)
 *
 *This function is a signal handler for SIGINT (Ctrl+C) and is responsible for
 *displaying the shell prompt and flushing the output buffer.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	putChar(BUF_FLUSH);
}
