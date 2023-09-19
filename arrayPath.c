#include "main.h"

/**
 * getPathValue - Get the value associated with a given name in the environment
 * @name: The name of the environment variable.
 *
 * Return: If found, return a pointer value; otherwise, NULL.
 */

char *getPathValue(const char *name)
{

	int counter = 0;
	size_t pathSize = strlen(name);

	while (environ[counter])
	{
		if (strncmp(environ[counter], name, pathSize) == 0)
		{
			return (environ[counter] + pathSize + 1);
		}
	counter++;
	}

	return (NULL);
}
