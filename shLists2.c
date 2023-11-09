#include "shell.h"

/**
 *listLen - Count the number of elements in a linked list.
 *@head: A pointer to the head of the list.
 *
 *Return: The number of elements in the list.
 */
size_t listLen(const list_t *head)
{
	size_t length = 0;

	while (head != NULL)
	{
		length++;
		head = head->next;
	}

	return (length);
}

/**
 *listToStrings - Convert a linked list of strings to an array of strings.
 *@head: A pointer to the head of the list.
 *
 *Return: An array of strings or NULL if allocation fails.
 */
char **listToStrings(list_t *head)
{
	list_t *node = head;
	size_t i, j;
	char **strs;
	char *str;

	if (!head)
		return (NULL);

	i = listLen(head);
	if (i == 0)
		return (NULL);

	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(strLen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		stringCpy(str, node->str);
		strs[i] = str;
	}

	strs[i] = NULL;
	return (strs);
}

/**
 *printList - Print the elements of a linked list.
 *@head: A pointer to the head of the list.
 *
 *Return: The number of elements printed.
 */
size_t printList(const list_t *head)
{
	size_t i = 0;
	char *numStr, *strToPrint;

	while (head)
	{
		numStr = convertNum(head->num, 10, 0);
		putChar(':');
		putChar(' ');
		strToPrint = (head->str) ? head->str : "(nil)";
		_puts(numStr);
		_puts(strToPrint);
		_puts("\n");
		free(numStr); /*Free the memory allocated by convertNum */
		head = head->next;
		i++;
	}

	return (i);
}

/**
 *nodeStartsWith - Find the first node with a string that starts with
 *a prefix and optional character.
 *@node: A pointer to the head of the list.
 *@prefix: The prefix to search for.
 *@c: Optional character filter.
 *
 *Return: A pointer to the found node or NULL if not found.
 */
list_t *nodeStartsWith(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = startsWith(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
		{
			return (node);
		}

		node = node->next;
	}

	return (NULL);
}

/**
 *getNodeIndex - Get the index of a node within a linked list.
 *@head: A pointer to the head of the list.
 *@node: The node whose index is to be found.
 *
 *Return: The index of the node or -1 if the node is not found.
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
		{
			return (i);
		}

		head = head->next;
		i++;
	}

	return (-1);
}
