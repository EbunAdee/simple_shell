#include "shell.h"

/**
 *myHelp - Displays command-line arguments.
 *@info: A pointer to the info_t structure.
 *
 *Return: Always returns 0.
 */
int myHelp(info_t *info)
{
	char **arg_array;
	int i;

	arg_array = info->argv;
	_puts("Help function called. Displaying command-line arguments:\n");

	/*Iterate through the command-line arguments and print each one */
	for (i = 0; arg_array[i] != NULL; i++)
	{
		_puts(arg_array[i]);
		_puts("\n");
	}

	return (0);
}

/**
 *myCd - Change the current working directory.
 *@info: A pointer to the info_t structure.
 *
 *Return: Always returns 0.
 */
int myCd(info_t *info)
{
	char *currentDir, *targetDir, buffer[1024];
	int chdir_ret;

	currentDir = getcwd(buffer, 1024); /*Get the current working directory */
	if (!currentDir)
		_puts("Failed to get current directory.\n"); /*Handle getcwd failure */

	if (!info->argv[1])
	{
		targetDir = getEnv(info, "HOME="); /*Change to the HOME directory */
		if (!targetDir)
			targetDir = getEnv(info, "PWD=");
	}
	else if (stringCmp(info->argv[1], "-") == 0)
	{
		targetDir = getEnv(info, "OLDPWD="); /*Change to the previous directory */
		if (!targetDir)
		{
			_puts(currentDir); /*Print the previous directory if it's not set */
			putChar('\n');
			return (1);
		}
	}
	else
	{
		targetDir = info->argv[1]; /*Change to the specified directory */
	}
	chdir_ret = chdir(targetDir);
	if (chdir_ret == -1)
	{
		printError(info, "can't cd to"); /*Hndle dir change failure*/
		ePuts(info->argv[1]);
		ePutChar('\n');
	}
	else
	{
		SetEnv(info, "OLDPWD", getEnv(info, "PWD=")); /*Update environ var */
		SetEnv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 *myExit - Exit the shell with an optional exit status.
 *@info: A pointer to the info_t structure.
 *
 *Return: The exit status code.
 */
int myExit(info_t *info)
{
	static int exit_status;

	if (info->argv[1])
	{
		/*If there is an argument, try to convert it to an integer */
		int exit_code = errAtoi(info->argv[1]);

		if (exit_code == -1)
		{
			info->status = 2;
			printError(info, "Illegal number: ");
			ePuts(info->argv[1]);
			ePutChar('\n');
			exit_status = 1;
		}
		else
		{
			info->err_num = exit_code;
			exit_status = -2;
		}
	}
	else
	{
		/*No argument provided, set default exit status */
		info->err_num = -1;
		exit_status = -2;
	}

	/*Additional logic can be added here if needed */
	return (exit_status);
}
