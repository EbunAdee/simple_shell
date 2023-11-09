#include "shell.h"

/**
 *getEnviron - Retrieves the environment variables as an array of strings.
 *
 *@info: Pointer to the info_t structure containing environment information.
 *
 *This function retrieves the environment variables and converts them into an
 *array of strings. If the environment has changed since the last retrieval,
 *it updates the 'info->environ' field.
 *
 *Return: A pointer to an array of strings containing environment variables.
 */
char **getEnviron(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = listToStrings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 *unSetEnv - Unsets an environment variable.
 *
 *@info: Pointer to the info_t structure containing environment information.
 *@var:  The name of the environment variable to unset.
 *
 *This function unsets the specified environment variable by removing it from
 *the 'info->env' linked list. It also updates the 'info->env_changed' field.
 *
 *Return: 0 if the variable was successfully unset, otherwise an error code.
 */
int unSetEnv(info_t *info, char *
	var)
{
	list_t *current_node = info->env;
	size_t index = 0;
	char *equals_position;

	if (!info || !
		var)
	{
		return (0);
	}

	while (current_node)
	{
		equals_position = startsWith(current_node->str,
			var);

		if (equals_position && *equals_position == '=')
		{
			info->env_changed = deleteNodeAtIndex(&(info->env), index);
			index = 0;
			current_node = info->env;
		}
		else
		{
			current_node = current_node->next;
			index++;
		}
	}

	return (info->env_changed);
}

/**
 *SetEnv - Sets or updates an environment variable.
 *
 *@info: Pointer to the info_t structure containing environment information.
 *@var:  The name of the environment variable to set or update.
 *@value: The value to assign to the environment variable.
 *
 *This function sets or updates the specified environment variable with the
 *given value. It handles memory allocation for the new environment entry.
 *
 *Return: 0 if the variable was successfully set or updated, otherwise an
 *error code.
 */
int SetEnv(info_t *info, char *
	var, char *value)
{
	char *p, *env_entry;
	list_t *node;

	if (!
		var || !value)
	{
		return (0); /*Invalid input */
	}

	env_entry = malloc(strLen(var) + strLen(value) + 2);
	if (!env_entry)
	{
		return (1); /*Memory allocation failed */
	}

	stringCpy(env_entry,
		var);
	stringCat(env_entry, "=");
	stringCat(env_entry, value);

	node = info->env;
	while (node)
	{
		p = startsWith(node->str,
			var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = env_entry;
			info->env_changed = 1;
			return (0); /*Environment variable updated */
		}

		node = node->next;
	}

	addNodeEnd(&(info->env), env_entry, 0);
	info->env_changed = 1;
	free(env_entry);
	return (0); /*New environment variable added */
}
