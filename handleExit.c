#include "main.h"
/**
 * exitProgram - Exits the program with a specified status code.
 * @argHolder: An array of strings containing arguments.
 * @input: The input string.
 *
 * Return: 0 if successful, 1 if an error occurred.
 */

int exitProgram(char **argHolder, char *input)
{
	char *tmp = argHolder[1];
	int position = 0;

	if (argHolder[1] == NULL)
	{
		free(argHolder);
		free(input);
		_exit(prog.status);
	}

	while (tmp[position] != '\0')
	{
		if (!isdigit(tmp[position]))
	{
		fprintf(stderr, "%s: %d: exit: Illegal number: %s\n",
				prog.name, prog.cmd_count, tmp);
		prog.status = 2;
		return (1);
	}
	position++;
	}
	prog.status = atoi(argHolder[1]);

	free(argHolder);
	free(input);
	_exit(prog.status);
}
