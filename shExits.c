#include "shell.h"

/**
 *_strnCpy - Copy at most n characters from src to dest
 *@dest: Destination string
 *@src: Source string
 *@n: Maximum number of characters to copy
 *
 *Return: A pointer to the destination string (dest).
 */
char *_strnCpy(char *dest, char *src, int n)
{
	char *s = dest;
	int i = 0;

	while (i < n)
	{
		if (src[i] != '\0')
		{
			dest[i] = src[i];
		}
		else
		{
			while (i < n)
			{
				dest[i] = '\0';
				i++;
			}

			break;
		}

		i++;
	}

	return (s);
}

/**
 *_strnCat - Concatenate at most n characters from src to dest
 *@dest: Destination string
 *@src: Source string
 *@n: Maximum number of characters to concatenate
 *
 *Return: A pointer to the destination string (dest).
 */
char *_strnCat(char *dest, const char *src, int n)
{
	char *s = dest;
	int i = 0, j = 0;

	/*Move to the end of the destination string */
	while (dest[i] != '\0')
	{
		i++;
	}

	/*Concatenate characters from src to dest, up to a maximum of n characters */
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	/*Ensure the destination string is null-terminated */
	dest[i] = '\0';

	return (s);
}

/**
 *_strChr - Search for the first occurrence of a character in a string
 *@s: The input string
 *@c: The character to search for
 *
 *Return: A pointer to the first occurrence of the character in the string,
 *        or NULL if the character is not found.
 */
char *_strChr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}

	return (NULL);
}
