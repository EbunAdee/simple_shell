#include "main.h"

/**
 * printEnvironment - Print the environment variables.
 * @envHandler: An array of strings containing environment variables.
 *
 * Return: 1 if successful, 0 otherwise.
 */

int printEnvironment(char **envHandler)
{
	int counter = 0;

	if (envHandler[1] != NULL)
		return (0);

	while (environ[counter] != NULL)
	{
		printString(environ[counter]);
		counter++;
	}

	return (1);
}
