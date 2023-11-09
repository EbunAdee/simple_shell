#include "shell.h"

/**
 *mySetEnv - Set an environment variable.
 *
 *@info: Pointer to the info_t structure.
 *
 *This function sets an environment variable
 *with the given name and value.
 *Return: 0 on success, 1 on failure.
 */
int mySetEnv(info_t *info)
{
	if (info->argc != 3)
	{
		ePuts("Incorrect number of arguments\n");
		return (1);
	}

	if (SetEnv(info, info->argv[1], info->argv[2]) != 0)
	{
		/*SetEnv failed */
		return (1);
	}

	/*SetEnv succeeded */
	return (0);
}

/**
 *myUnsetEnv - Unset one or more environment variables.
 *
 *@info: Pointer to the info_t structure.
 *
 *This function unsets one or more environment
 *variables based on the given arguments.
 *Return: 0 on success, 1 on failure.
 */
int myUnsetEnv(info_t *info)
{
	int i;

	if (info->argc <= 1)
	{
		ePuts("Too few arguments.\n");
		return (1);
	}

	for (i = 1; i < info->argc; i++)
	{
		if (unSetEnv(info, info->argv[i]) != 0)
		{ /*unSetEnv failed for one of the variables */
			return (1);
		}
	}

	/*All unSetEnv calls succeeded */
	return (0);
}

/**
 *popuEnvList - Populate the environment list.
 *
 *@info: Pointer to the info_t structure.
 *
 *This function populates the environment list
 *with the current environment variables.
 *Return: 0 on success, 1 on failure.
 */
int popuEnvList(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		addNodeEnd(&node, environ[i], 0);
	}

	info->env = node;
	return (0);
}

/**
 *getEnv - Get the value of an environment variable.
 *
 *@info: Pointer to the info_t structure.
 *@name: The name of the environment variable.
 *
 *This function retrieves the value of the specified environment variable.
 *
 *Return: A pointer to the value if found, NULL if not found.
 */
char *getEnv(info_t *info, const char *name)
{
	char *p;
	list_t *node = info->env;

	while (node)
	{
		p = startsWith(node->str, name);

		if (p != NULL && p[0] != '\0')
		{
			return (p);
		}

		node = node->next;
	}

	return (NULL);
}

/**
 *myEnv - Print the current environment.
 *
 *@info: Pointer to the info_t structure.
 *
 *This function prints the current environment variables.
 *
 *Return: Always returns 0.
 */
int myEnv(info_t *info)
{
	printListStr(info->env);
	return (0);
}
