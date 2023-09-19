#include "main.h"

/**
 * processArguments - Splits a string into an array of tokens using a delimiter
 *
 * @input: The input string to be split.
 * @delimiter: The delimiter used for splitting.
 *
 * Return: An array of strings containing the tokens, or NULL on failure.
 */

char **processArguments(char *input, char *delimiter)
{
	int i = 0;
	int count = 0;
	char *stringHolder = NULL;
	char *token = NULL;
	char **argArray = NULL;

	stringHolder = strdup(input);
	if (!stringHolder)
		return (NULL);

	token = strtok(stringHolder, delimiter);
	while (token)
	{
		count++;
		token = strtok(NULL, delimiter);
	}

	argArray = malloc(sizeof(char *) * (count + 1));
	if (!argArray)
	{
		free(stringHolder);
		return (NULL);
	}

	i = 0;
	token = strtok(input, delimiter);
	while (token)
	{
		argArray[i++] = token;
		token = strtok(NULL, delimiter);
	}

	argArray[i] = NULL;
	free(stringHolder);
	return (argArray);
}
