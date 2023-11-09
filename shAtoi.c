#include "shell.h"

/**
 *shAtoi - Convert a string to an integer.
 *@s: The input string to be converted.
 *
 *Return: The integer value represented by the string.
 */
int shAtoi(const char *s)
{
	int i = 0;
	int sign = 1;
	int flag = 0;
	int output = 0;

	unsigned int result = 0;

	while (s[i] != '\0' && flag != 2)
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}

		i++;
	}

	if (sign == -1)
	{
		output = -result;
	}
	else
	{
		output = result;
	}

	return (output);
}

/**
 *isAlpha - Check if a character is an alphabetic character (A-Z or a-z).
 *@c: The character to check.
 *
 *Return: 1 if the character is an alphabetic character, 0 otherwise.
 */
int isAlpha(int c)
{
	int isLowerCase = (c >= 'a' && c <= 'z');
	int isUpperCase = (c >= 'A' && c <= 'Z');

	if (isLowerCase || isUpperCase)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 *isDelim - Check if a character is a delimiter in a given set of delimiters.
 *@c: The character to check.
 *@delim: The set of delimiters to compare against.
 *
 *Return: 1 if the character is a delimiter, 0 otherwise.
 */
int isDelim(char c, const char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}

	return (0);
}

/**
 *interact - Check if the program is running in an interactive terminal.
 *@info: A pointer to information about the program's input and output.
 *
 *Return: 1 if running in an interactive terminal, 0 otherwise.
 */
int interact(info_t *info)
{
	int isTerminal = isatty(STDIN_FILENO);
	int isReadFDValid = info->readfd <= 2;

	if (isTerminal && isReadFDValid)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
