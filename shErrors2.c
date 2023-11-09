#include "shell.h"

/**
 *errAtoi - Convert a string to an integer
 *@s: The input string to convert
 *
 *Return: The integer value or INT_MIN/INT_MAX on overflow/underflow
 */
int errAtoi(char *s)
{
	int result = 0;
	int sign = 1; /*Default positive sign */

	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1; /*Set the sign to negative if '-' is present */
		s++; /*Skip the sign character */
	}

	for (; *s != '\0'; s++)
	{
		if (*s >= '0' && *s <= '9')
		{
			int digit = *s - '0';

			/*Check for potential integer overflow/underflow */
			if (result > (INT_MAX - digit) / 10 || result < (INT_MIN + digit) / 10)
			{
				return ((sign == 1) ? INT_MAX : INT_MIN);
			}

			result = result * 10 + sign * digit;
		}
		else
		{
			return (-1); /*Invalid character in the input string */
		}
	}

	return (result);
}

/**
 *printError - Print an error message with formatting
 *@info: Information about the error context
 *@estr: The error string to print
 */
void printError(info_t *info, char *estr)
{
	/*Print the filename followed by ": " */
	ePuts(info->fname);
	ePuts(": ");

	/*Print the line count followed by ": " */
	printD(info->line_count, STDERR_FILENO);
	ePuts(": ");

	/*Print the program name (from argv[0]) followed by ": " */
	ePuts(info->argv[0]);
	ePuts(": ");

	/*Print the error string (estr) */
	ePuts(estr);
}

/**
 *printD - Print an integer to a file descriptor
 *@input: The integer to print
 *@fd: The file descriptor to print to
 *
 *Return: The number of characters printed
 */
int printD(int input, int fd)
{
	int (*_putChar)(char) = (fd == STDERR_FILENO) ? ePutChar : putChar;
	int count = 0;
	int divisor, digit;
	bool leadingZero;

	if (input < 0)
	{
		_putChar('-');
		input = -input;
		count++;
	}

	leadingZero = true;

	for (divisor = 1000000000; divisor >= 1; divisor /= 10)
	{
		digit = input / divisor;
		input %= divisor;

		if (digit > 0 || !leadingZero)
		{
			_putChar('0' + digit);
			count++;
			leadingZero = false;
		}
	}

	return (count);
}

/**
 *convertNum - Convert a number to a string with a specified base
 *@num: The number to convert
 *@base: The base for conversion (e.g., 10 for decimal)
 *@flags: Flags for conversion options
 *
 *Return: The pointer to the converted string
 */
char *convertNum(long int num, int base, int flags)
{
	static char buffer[50];
	static char *array;
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	/*Determine the character array to use for conversion based on flags */
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";

	/*Check if the number is negative and flags allow for signed conversion */
	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		sign = '-';
		n = -num;
	}

	ptr = &buffer[49];
	*ptr = '\0';

	/*Convert the number to the specified base */
	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	/*Add the sign character if the number was negative */
	if (sign)
		*
		--ptr = sign;

	/*Return the pointer to the converted string */
	return (ptr);
}

/**
 *removeComm - Remove a comment from a string
 *@buf: The input string to remove the comment from
 */
void removeComm(char *buf)
{
	int i = 0;
	int commentStart = -1;

	/*Search for the '#' character and check for the space before it */
	while (buf[i] != '\0')
	{
		if (buf[i] == '#' && (i == 0 || buf[i - 1] == ' '))
		{
			commentStart = i;
			break;
		}

		i++;
	}

	/*Remove the comment if found */
	if (commentStart != -1)
	{
		buf[commentStart] = '\0';
	}
}
