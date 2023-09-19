#include "main.h"
#include "program.h"
/**
 * printString - Prints a string followed by a newline character
 * @string: The string to be printed
 */
void printString(char *string);
/**
 * main - Entry point of the program
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 * Return: Always 0
 */
int main(int argc __attribute__ ((unused)), char **argv)
{
	char *userInput = NULL;
	size_t len = 0;
	ssize_t nread;
	program_t prog = {NULL, 0, 0};

	prog.name = argv[0];

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "$ ", 2);
		}
		nread = getline(&userInput, &len, stdin);
		prog.cmd_count++;
		if (nread < 1)
		{
			if (isatty(STDIN_FILENO))
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			free(userInput);
			exit(prog.status);
		}

		userInput[nread - 1] = '\0';
		handlePrompt(userInput, argv[0]);
	}
	return (0);
}
/**
 * printString - Prints a string followed by a newline character
 * @string: The string to be printed
 */
void printString(char *string)
	{
	int counter = 0;

	while (string[counter])
	{
		write(STDOUT_FILENO, &string[counter], 1);
		counter++;
	}
	write(STDOUT_FILENO, "\n", 1);
}
