#include "shell.h"

/**
 *printAlias - Print an alias from a list node
 *@node: Pointer to the list node containing the alias
 *
 *This function prints an alias from a given list node.
 *
 *Return: 0 on success, 1 on failure
 */
int printAlias(list_t *node)
{
	char *equalSignPos;
	char *aliasName;

	if (node)
	{
		equalSignPos = _strChr(node->str, '=');
		for (aliasName = node->str; aliasName <= equalSignPos; aliasName++)
			putChar(*aliasName);

		putChar('\'');
		_puts(equalSignPos + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}

/**
 *unsetAlias - Unset an alias in the info structure
 *@info: Pointer to the info structure
 *@str: Alias to unset
 *
 *This function unsets an alias in the info structure.
 *
 *Return: 0 on success, 1 on failure
 */
int unsetAlias(info_t *info, char *str)
{
	char *equalSignPos;
	char originalChar;
	int result;

	equalSignPos = _strChr(str, '=');
	if (!equalSignPos)
		return (1);

	originalChar = *equalSignPos;
	*equalSignPos = 0;

	result = deleteNodeAtIndex(&(info->alias), getNodeIndex
		(info->alias, nodeStartsWith(info->alias, str, -1)));

	*equalSignPos = originalChar;
	return (result);
}

/**
 *setAlias - Set an alias in the info structure
 *@info: Pointer to the info structure
 *@str: Alias to set
 *
 *This function sets an alias in the info structure.
 *
 *Return: 0 on success, 1 on failure
 */
int setAlias(info_t *info, char *str)
{
	char *equalSignPos = _strChr(str, '=');
	int result;

	if (!equalSignPos)
		return (1);

	if (!*++equalSignPos)
		return (unsetAlias(info, str));

	unsetAlias(info, str);
	result = addNodeEnd(&(info->alias), str, 0) == NULL;
	return (result);
}

/**
 *myAlias - Handle alias commands
 *@info: Pointer to the info structure
 *
 *This function handles alias commands,
 *including setting and printing aliases.
 *Return: Always returns 0
 */
int myAlias(info_t *info)
{
	int i;
	char *equalSignPos;
	list_t *node;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)

		{

			printAlias(node);
			node = node->next;
		}

		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		equalSignPos = _strChr(info->argv[i], '=');
		if (equalSignPos)
			setAlias(info, info->argv[i]);
		else
			printAlias(nodeStartsWith(info->alias, info->argv[i], '='));
	}

	return (0);
}

/**
 *myHistory - Print the command history
 *@info: Pointer to the info structure
 *
 *This function prints the command history.
 *
 *Return: Always returns 0
 */
int myHistory(info_t *info)
{
	printList(info->history);
	return (0);
}
