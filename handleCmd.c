#include "main.h"

/**
 * executeCommand - Execute a command with arguments in a new process.
 *
 * @argArray: Array of command and its arguments.
 * @programName: Name of the program for error reporting.
 */
void executeCommand(char **argArray, char *programName)
{
	int waitStatus;
	/* pid_t childPid; */
	char *command = argArray[0];

	/* Check if the command contains a slash */
	if (checkSlash(command) == 0)
	{
		execExternalCmd(argArray, programName, &waitStatus);
	}
	else
	{
		execCmdPath(argArray, programName, command);
	}
}

/**
 * execExternalCmd - Execute an external command in a new process.
 *
 * @argArray: Array of command and its arguments.
 * @programName: Name of the program for error reporting.
 * @waitStatus: Pointer to variable to store child process's exit status.
 */
void execExternalCmd(char **argArray, char *programName, int *waitStatus)
{
	pid_t childPid = fork();

	if (childPid == -1)
	{
		perror("Fork error");
	}
	else if (childPid == 0)
	{
		/* Child process */
		if (execve(argArray[0], argArray, environ) == -1)
		{
			perror(programName);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		if (wait(waitStatus) == -1)
		{
			perror("Wait error");
		}
		else if (WIFEXITED(*waitStatus))
		{
			prog.status = WEXITSTATUS(*waitStatus);
		}
	}
}

/**
 * execCmdPath - Execute a command from the PATH environment variable.
 *
 * @argArray: Array of command and its arguments.
 * @programName: Name of the program for error reporting.
 * @command: The command to be executed.
 */
void execCmdPath(char **argArray, char *programName, char *command)
{
	char *modifiedCommand = modifyBuffer(command);

	if (!modifiedCommand)
	{
		prog.status = 127;
		fprintf(stderr, "%s: %d: %s: not found\n", prog.name,
prog.cmd_count, command);
	}
	else
	{
		argArray[0] = modifiedCommand;
		executeCommand(argArray, programName);
	}
}
