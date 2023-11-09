#include "shell.h"

/**
 *isChain - Check if the given character in a command buffer
 *represents a chain operator(|, ||, &, &&, ;).
 *
 *@info: Pointer to the information struct.
 *@buf: Command buffer.
 *@p: Pointer to the current index in the buffer.
 *
 *Return: 1 if the character is a chain operator, 0 otherwise.
 */
int isChain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	switch (buf[j])
	{
		case '|':
			if (buf[j + 1] == '|')
			{
				buf[j] = 0;
				j++;
				info->cmd_buf_type = CMD_OR;
			}
			else
			{
				return (0);
			}

			break;
		case '&':
			if (buf[j + 1] == '&')
			{
				buf[j] = 0;
				j++;
				info->cmd_buf_type = CMD_AND;
			}
			else
			{
				return (0);
			}

			break;
		case ';':
			buf[j] = 0;
			info->cmd_buf_type = CMD_CHAIN;
			break;
		default:
			return (0);
	}

	*p = j;
	return (1);
}

/**
 *checkChain - Check if a chain operator requires a command buffer change.
 *
 *@info: Pointer to the information struct.
 *@buf: Command buffer.
 *@p: Pointer to the current index in the buffer.
 *@i: Index of the chain operator in the buffer.
 *@len: Length of the buffer.
 */
void checkChain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if ((info->cmd_buf_type == CMD_AND && info->status) ||
		(info->cmd_buf_type == CMD_OR && !info->status))
	{
		buf[i] = 0;
		j = len;
	}

	*p = j;
}

/**
 *replaceAlias - Replace the alias in the command with its value.
 *
 *@info: Pointer to the information struct.
 *
 *Return: 1 if the alias is successfully replaced, 0 otherwise.
 */
int replaceAlias(info_t *info)
{
	int i = 0;
	list_t *node;
	char *p;

	while (i < 10)
	{
		node = nodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);
		p = _strChr(node->str, '=');
		if (!p)
			return (0);

		p = stringDup(p + 1);
		if (!p)
			return (0);

		free(node->str); /*Free the old alias string */
		info->argv[0] = p;

		i++;
	}

	return (1);
}

/**
 *replaceVars - Replace variables in the command with their values.
 *
 *@info: Pointer to the information struct.
 *
 *Return: Always returns 0 (no error handling specified).
 */
int replaceVars(info_t *info)
{
	int i = 0;
	list_t *node;

	while (info->argv[i])
	{
		if (info->argv[i][0] == '$' && info->argv[i][1])
		{
			char *replacement = NULL;

			switch (info->argv[i][1])
			{
				case '?':
					replacement = convertNum(info->status, 10, 0);
					break;
				case '$':
					replacement = convertNum(getpid(), 10, 0);
					break;
				default:
					node = nodeStartsWith(info->env, &info->argv[i][1], '=');
					if (node)
					{
						replacement = _strChr(node->str, '=') + 1;
					}
					else
					{
						replacement = "";
					}

					break;
			}

			replaceString(&(info->argv[i]), stringDup(replacement));
		}

		i++;
	}

	return (0);
}

/**
 *replaceString - Replace an old string with a new one.
 *
 *@old: Pointer to the old string to be replaced.
 *@new: New string to replace the old one.
 *
 *Return: 1 if the replacement is successful, 0 if memory allocation fails.
 */
int replaceString(char **old, char *new)
{
	if (new == NULL)
	{
		/*Error: Memory allocation failed for the new string */
		return (0);
	}

	free(*old);
	*old = new;
	return (1);
}
