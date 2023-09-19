#include "main.h"
/**
 * modifyBuffer - Modifies a command by appending directories from PATH.
 * @command: The command to be modified.
 * Return: A modified command if found in PATH, otherwise NULL.
 */
char *modifyBuffer(char *command)
{
	char pathStr[1024];
	char **directories;
	int counter = 0;
	int len = strlen(command);
	/* Get the PATH environment variable value */
	char *pathValue = getPathValue("PATH");

	if (pathValue == NULL)
	{
		return (NULL);
	}
	strcpy(pathStr, pathValue);
	directories = processArguments(pathStr, ":");

	while (directories[counter])	/* Iterate through directories in PATH */
	{
		char *modifiedCommand;
		int bufLen = strlen(directories[counter]);

		/* Allocate memory for the modified command */
		modifiedCommand = malloc(sizeof(char) * (bufLen + len + 2));
		if (modifiedCommand == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		strcpy(modifiedCommand, directories[counter]);	/* Construct modified cmd */
		strcat(modifiedCommand, "/");
		strcat(modifiedCommand, command);

		if (checkCommand(modifiedCommand) == 0)		/* Check if modified cmd exists */
		{
			free(directories);
			return (modifiedCommand);
		}
		free(modifiedCommand);
		counter++;
	}
	free(directories);
	return (NULL);
}
/**
 * checkCommand - Checks if a command exists in the file system.
 * @command: The command to be checked.
 * Return: 0 if the command exists, -1 otherwise.
 */
int checkCommand(char *command)
{
	return (access(command, F_OK));
}
