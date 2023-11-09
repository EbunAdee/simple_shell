#include "shell.h"

/**
 *putFd - Writes a character to a file descriptor or flushes a buffer.
 *
 *@c: The character to write or a special flag (BUF_FLUSH).
 *@fd: The file descriptor to write to.
 *
 *Return: 1 if successful, 0 on error.
 */
int putFd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i); /*Flush the buffer to the specified file descriptor */
		i = 0;
	}

	if (c != BUF_FLUSH)
	{
		buf[i++] = c; /*Add the character to the buffer */
	}

	return (1);
}

/**
 *putsFd - Writes a string to a file descriptor.
 *
 *@str: The string to write.
 *@fd: The file descriptor to write to.
 *
 *Return: The total count of characters written,
 *or 0 if the input string is NULL.
 */
int putsFd(char *str, int fd)
{
	int i;

	if (!str)
	{
		return (0); /*Return 0 if the input string is NULL */
	}

	i = 0;
	while (*str)
	{
		i += putFd(*str, fd); /*Process and count each character written */
		str++;
	}

	return (i); /*Return the total count of characters written */
}

/**
 *ePuts - Writes a string to the standard error (stderr).
 *
 *@str: The string to write.
 */
void ePuts(char *str)
{
	int i;

	if (str == NULL)
	{
		return; /*Do nothing if str is NULL */
	}

	i = 0;
	while (str[i] != '\0')
	{
		ePutChar(str[i]); /*Print each character in the string */
		i++;
	}
}

/**
 *ePutChar - Writes a character to the standard error (stderr)
 * or flushes a buffer.
 *
 *@c: The character to write or a special flag (BUF_FLUSH).
 *
 *Return: 1 if successful, 0 on error.
 */
int ePutChar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i); /*Flush the buffer to stderr */
		i = 0;
	}

	if (c != BUF_FLUSH)
	{
		buf[i++] = c; /*Add the character to the buffer */
	}

	return (1);
}
