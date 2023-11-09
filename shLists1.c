#include "shell.h"

/**
 *addNode - Add a new node at the beginning of a linked list.
 *@head: A pointer to the pointer to the head of the list.
 *@str: The string to be stored in the new node.
 *@num: An integer to be stored in the new node.
 *
 *Return: A pointer to the newly created node, or NULL on failure.
 */
list_t *addNode(list_t **head, const char *str, int num)
{
	list_t *new_head = NULL;
	list_t *new_node = NULL;

	if (!head)
		return (NULL);

	new_node = (list_t *) malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	memSet((void *) new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = stringDup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;
	new_head = new_node;

	return (new_head);
}

/**
 *addNodeEnd - Add a new node at the end of a linked list.
 *@head: A pointer to the pointer to the head of the list.
 *@str: The string to be stored in the new node.
 *@num: An integer to be stored in the new node.
 *
 *Return: A pointer to the newly created node, or NULL on failure.
 */
list_t *addNodeEnd(list_t **head, const char *str, int num)
{
	list_t *new_node = NULL;
	list_t *node = NULL;

	if (!head)
		return (NULL);

	new_node = (list_t *) malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	memSet((void *) new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = stringDup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	node = *head;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}

	return (new_node);
}

/**
 *printListStr - Print the strings stored in the linked list.
 *@h: A pointer to the head of the list.
 *
 *Return: The number of nodes in the list.
 */
size_t printListStr(const list_t *h)
{
	size_t i = 0;
	const list_t *current_node = h;

	while (current_node)
	{
		_puts(current_node->str ? current_node->str : "(nil)");
		_puts("\n");
		current_node = current_node->next;
		i++;
	}

	return (i);
}

/**
 *deleteNodeAtIndex - Delete a node at the specified index in the linked list.
 *@head: A pointer to the pointer to the head of the list.
 *@index: The index of the node to be deleted.
 *
 *Return: 1 on success, 0 on failure.
 */
int deleteNodeAtIndex(list_t **head, unsigned int index)
{
	list_t *node = NULL;
	list_t *prev_node = NULL;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (index == 0)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}

		i++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 *freeList - Free all nodes in the linked list and set the head to NULL.
 *@head_ptr: A pointer to the pointer to the head of the list.
 */
void freeList(list_t **head_ptr)
{
	list_t *node = NULL;
	list_t *next_node = NULL;
	list_t *head = NULL;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}
