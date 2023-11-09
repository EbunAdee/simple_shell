#include "shell.h"

/**
 *stringCpy - Copy a string from src to dest
 *@dest: Destination buffer
 *@src: Source string
 *
 *Return: Pointer to the destination buffer
 */
char *stringCpy(char *dest, const char *src)
{
	int i = 0;

	if (dest == NULL || src == NULL || dest == src)
		return (dest);

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';

	return (dest);
}

/**
 *stringDup - Duplicate a string
 *@str: Source string to be duplicated
 *
 *Return: Pointer to the duplicated string, or NULL if allocation fails
 */
char *stringDup(const char *str)
{
	int length = 0;
	char *ret;
	int i;

	if (str == NULL)
		return (NULL);

	while (str[length] != '\0')
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	for (i = 0; i < length; i++)
		ret[i] = str[i];
	ret[length] = '\0';

	return (ret);
}

/**
 *_puts - Print a string to the standard output
 *@str: String to be printed
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	for (i = 0; str[i] != '\0'; i++)
	{
		putChar(str[i]);
	}
}

/**
 *putChar - Write a character to the standard output
 *@c: Character to be written
 *
 *Return: 1 on success, -1 on failure
 */
int putChar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	switch (c)
	{
		case BUF_FLUSH:
			write(1, buf, i);
			i = 0;
			break;
		default:
			if (i >= WRITE_BUF_SIZE)
			{
				write(1, buf, i);
				i = 0;
			}

			buf[i++] = c;
			break;
	}

	return (1);
}
