#include "shell.h"

/**
 *bFree - Frees a pointer and sets it to NULL.
 *@ptr: A pointer to a pointer that needs to be freed.
 *
 *This function frees the memory pointed to by the given pointer and sets
 *the pointer to NULL to avoid any dangling references.
 *
 *Return: 1 if the memory was successfully freed, 0 otherwise.
 */
int bFree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}

	return (0);
}
