#include "main.h"

/**
 * handlePrompt - Handles user input and executes commands w/ var replacement.
 * @input: The user input string.
 * @programName: The name of the program.
 */
void handlePrompt(char *input, char *programName)
{
	/* Split the input into arguments and store them in argHolder */
	char **argHolder = processArguments(input, " \t");

	/* If argHolder is NULL or the first argument is empty, return */
	if (!argHolder || !argHolder[0])
	{
		free(argHolder);
		return;
	}

	/* Replace variables like "$?" and "$$" in the arguments */
	replaceVariables(argHolder);

	/* Check if the input corresponds to a built-in command and execute it */
	if (checkAndExecuteBuiltins(argHolder, input))
	{
		free(argHolder);
		return;
	}

	/* If it's not a built-in command, check and execute an external command */
	if (!checkAndExecuteCommand(argHolder, programName))
	{
		free(argHolder);
		return;
	}

	free(argHolder);
}

/**
 * replaceVariables - Replaces special variables in the argument list.
 * @args: The array of command arguments.
 */
void replaceVariables(char **args)
{
	int i = 0;

	while (args[i] != NULL)
	{
		if (strcmp(args[i], "$?") == 0)
		{
			/* Replace "$?" with the exit code of the previous command */
			char exitCodeStr[16];

			snprintf(exitCodeStr, sizeof(exitCodeStr), "%d", prog.status);
			args[i] = strdup(exitCodeStr);
		}
		else if (strcmp(args[i], "$$") == 0)
		{
			/* Replace "$$" with the process ID of the shell */
			pid_t pid = getpid();
			char pidStr[16];

			snprintf(pidStr, sizeof(pidStr), "%d", pid);
			args[i] = strdup(pidStr);
		}
		i++;
	}
}

/**
 * checkAndExecuteBuiltins - Checks if command is a built-in and executes it.
 * @args: The array of command arguments.
 * @input: The user input string.
 * Return: 1 or 0
 */
int checkAndExecuteBuiltins(char **args, char *input)
{
	/* Check if the command is a built-in and execute it */
	int builtinStatus = checkBuiltin(args, input);

	return (builtinStatus == 1);
}

/**
 * checkAndExecuteCommand - Checks if cmd is an external cmd and executes it.
 * @args: The array of command arguments.
 * @programName: The name of the program.
 * Return: 1 or 0
 */
int checkAndExecuteCommand(char **args, char *programName)
{
	/* Check if the command exists in the system's PATH and execute it */
	int commandStatus = checkCommand(args[0]);
	int slashStatus = checkSlash(args[0]);

	if (slashStatus == 0 || commandStatus == 0)
	{
		executeCommand(args, programName);
	}
	else
	{
		char *originalCommand = args[0];
		char *modifiedCommand = modifyBuffer(originalCommand);

		if (!modifiedCommand)
		{
			prog.status = 127;
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog.name, prog.cmd_count, originalCommand);
		}
		else
		{
			args[0] = modifiedCommand;
			executeCommand(args, programName);
		}
	}
	return (1);
}
