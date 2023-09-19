#include "main.h"

/**
 * checkSlash - Checks if a string contains a slash character.
 * @input: The input string to check.
 *
 * Return: 0 if a slash is found, -1 otherwise.
 */

int checkSlash(char *input)
{
	while (*input)
	{
		if (*input++ == '/')
		{
			return (0);
		}
	}

	return (-1);
}
