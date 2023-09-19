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
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{
		perror("Fork error");
	} else if (childPid == 0)
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
		if (wait(&waitStatus) == -1)
		{
			perror("Wait error");
		}
		else
		{
			if (WIFEXITED(waitStatus))
			{
				prog.status = WEXITSTATUS(waitStatus);
			}
		}
	}
}
