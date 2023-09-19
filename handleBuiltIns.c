#include "main.h"

/**
 * checkBuiltin - Check if the command is a built-in command and execute.
 * @argHolder: An array of strings containing arguments.
 * @input: The input string.
 *
 * Return: 1 if a built-in command was executed, 0 otherwise.
 */

int checkBuiltin(char **argHolder, char *input)
{
	int executed = 0;

	if (strcmp(argHolder[0], "exit") == 0)
	{
		exitProgram(argHolder, input);
		executed = 1;
	}
	else if (strcmp(argHolder[0], "env") == 0)
	{
		executed = printEnvironment(argHolder);
	}

	return (executed);
}
