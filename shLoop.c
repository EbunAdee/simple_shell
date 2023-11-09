#include "shell.h"

/**
 *hsh - Main function for the shell.
 *@info: The info_t structure to store shell information.
 *@av: An array of strings representing command-line arguments.
 *Return: The exit status or result of the last built-in command.
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clearInfo(info);
		if (interact(info))
			_puts("Shell$ ");
		ePutChar(BUF_FLUSH);
		r = getInput(info);
		if (r != -1)
		{
			setInfo(info, av);
			builtin_ret = findBuiltin(info);
			if (builtin_ret == -1)
				findCmd(info);
		}
		else if (interact(info))
			putChar('\n');
		freeInfo(info, 0);
	}

	writeHistory(info);
	freeInfo(info, 1);

	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}

	if (!interact(info) && info->status)
		exit(info->status);

	return (builtin_ret);
}

/**
 *findBuiltin - Find a built-in command and execute it.
 *@info: The info_t structure to store shell information.
 *Return: The return value of executed built-in command, or -1 if not found.
 */
int findBuiltin(info_t *info)
{
	int i = 0;
	int built_in_ret = -1;
	builtinT builtintbl[] = {
		{ "exit", myExit
		},
		{ "env", myEnv
		},
		{ "help", myHelp
		},
		{ "history", myHistory
		},
		{ "setenv", mySetEnv
		},
		{ "unsetenv", myUnsetEnv
		},
		{ "cd", myCd
		},
		{ "alias", myAlias
		},
		{
			NULL, NULL
		}
	};

	while (builtintbl[i].type)
	{
		if (stringCmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}

		i++;
	}

	return (built_in_ret);
}

/**
 *findCmd - Find and execute a non-built-in command.
 *@info: The info_t structure to store shell information.
 */
void findCmd(info_t *info)
{
	char *path = NULL;
	int i = 0;
	int k = 0;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	while (info->arg[i])
	{
		if (!isDelim(info->arg[i], " \t\n"))
		{
			k++;
		}

		i++;
	}
	if (k == 0)
		return;

	path = findPath(info, getEnv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkCmd(info);
	}
	else if (interact(info) || getEnv(info, "PATH=") ||
		info->argv[0][0] == '/' || isCmd(info, info->argv[0]))
	{
		forkCmd(info);
	}
	else if (*(info->arg) != '\n')
	{
		info->status = 127;
		printError(info, "not found\n");
	}
}

/**
 *forkCmd - Fork and execute a non-built-in command.
 *@info: The info_t structure to store shell information.
 */
void forkCmd(info_t *info)
{
	pid_t child_pid;
	int wait_status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, getEnviron(info)) == -1)
		{
			if (errno == EACCES)
			{
				freeInfo(info, 1);
				exit(126);
			}
			else
			{
				freeInfo(info, 1);
				exit(1);
			}
		}
	}
	else
	{
		waitpid(child_pid, &wait_status, 0);

		if (WIFEXITED(wait_status))
		{
			info->status = WEXITSTATUS(wait_status);
			if (info->status == 126)
			{
				printError(info, "Permission denied\n");
			}
		}
	}
}
