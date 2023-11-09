#include "shell.h"

/**
 *clearInfo - Clear the fields of an info_t structure.
 *@info: Pointer to the info_t structure to clear.
 *
 *This function clears the fields of the info_t structure pointed to by 'info'.
 */
void clearInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 *freeInfo - Free memory associated with an info_t structure.
 *@info: Pointer to the info_t structure to free memory for.
 *@freeAll: Flag indicating whether to free all related data
 * or just the basics.
 *
 *This function frees memory associated with the info_t
 * structure pointed to by 'info'.
 *If 'freeAll' is set, it will also free other related data
 * such as command history and environment variables.
 */
void freeInfo(info_t *info, int freeAll)
{
	fFree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (freeAll)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeList(&(info->env));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		fFree(info->environ);
		info->environ = NULL;
		bFree((void **) info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		putChar(BUF_FLUSH);
	}
}

/**
 *setInfo - Set the fields of an info_t structure based on input arguments.
 *@info: Pointer to the info_t structure to populate.
 *@av: An array of strings representing the command and its arguments.
 *
 *This function populates the fields of the info_t structure
 * pointed to by 'info'
 *based on the input arguments in the 'av' array. It also performs
 * alias and variable replacement.
 */
void setInfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];

	if (info->arg)
	{
		info->argv = strTow(info->arg, " \t");

		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);

			if (info->argv)
			{
				info->argv[0] = stringDup(info->arg);
				info->argv[1] = NULL;
			}
		}

		if (info->argv)
		{
			while (info->argv[i])
			{
				i++;
			}
		}

		info->argc = i;

		replaceAlias(info);
		replaceVars(info);
	}
}
