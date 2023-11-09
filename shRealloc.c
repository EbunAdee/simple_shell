#include "shell.h"

/**
 *memSet - Set a portion of memory to a specified byte value
 *@s: Pointer to the memory region to be set
 *@b: The byte value to set in the memory region
 *@n: Number of bytes to set
 *
 *Return: Pointer to the modified memory region (same as input s)
 */
char *memSet(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}

	return (s);
}

/**
 *fFree - Free a dynamically allocated array of strings and the array itself
 *@pp: Pointer to an array of strings
 */
void fFree(char **pp)
{
	char **a = pp;

	if (!pp)
	{
		return;
	}

	while (*pp)
	{
		free(*pp);
		pp++;
	}

	free(a);
}

/**
 *reAlloc - Reallocate memory for a dynamically allocated block
 *@ptr: Pointer to the memory block to be reallocated
 *@old_size: Size of the current memory block in bytes
 *@new_size: Size to which the memory block should be reallocated
 *
 *Return: Pointer to the reallocated memory block or NULL if reallocation fails
 */
void *reAlloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *p;
	unsigned int i;

	if (!ptr)
	{
		return (malloc(new_size));
	}

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
	{
		return (ptr);
	}

	p = malloc(new_size);
	if (!p)
	{
		return (NULL);
	}

	old_size = old_size < new_size ? old_size : new_size;

	for (i = 0; i < old_size; i++)
	{
		((char *) p)[i] = ((char *) ptr)[i];
	}

	free(ptr);
	return (p);
}
