#include "shell.h"

/**
 *strLen - Returns the length of a string.
 *@s: The input string.
 *
 *Return: The length of the string.
 */
int strLen(char *s)
{
	int i = 0;

	if (!s)
	{
		return (0);
	}

	for (i = 0; s[i] != '\0'; i++)
	{
		/*No need to increment i explicitly in the loop header */
	}

	return (i);
}

/**
 *stringCmp - Compares two strings.
 *@s1: The first string.
 *@s2: The second string.
 *
 *Return: 0 if the strings are equal, a negative value if s1<s2,
 *and a positive value if s1 > s2.
 */
int stringCmp(char *s1, char *s2)
{
	int result = 0;

	for (; *s1 && *s2; s1++, s2++)
	{
		if (*s1 != *s2)
		{
			result = *s1 - *s2;
			break;
		}
	}

	if (result == 0)
	{
		result = (*s1 == *s2) ? 0 : ((*s1 < *s2) ? -1 : 1);
	}

	return (result);
}

/**
 *startsWith - Checks if a string starts with a given substring.
 *@haystack: The string to search in.
 *@needle: The substring to search for at the beginning of haystack.
 *
 *Return: A pointer to the start of the substring in the string if found,
 *or NULL if the substring is not at the beginning of the string.
 */
char *startsWith(const char *haystack, const char *needle)
{
	while (*haystack && *needle)
	{
		if (*haystack != *needle)
		{
			haystack = NULL;
			break;
		}

		haystack++;
		needle++;
	}

	if (*needle)
	{
		return (NULL);
	}
	else
	{
		return ((char *) haystack);
	}
}

/**
 *stringCat - Concatenates two strings.
 *@dest: The destination string.
 *@src: The source string to be appended to the destination.
 *
 *Return: A pointer to the destination string (dest).
 */
char *stringCat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
	{
		dest++;
	}

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';

	return (ret);
}
