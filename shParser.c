#include "shell.h"

/**
 *isCmd - Check if a file exists at the given path.
 *
 *@info: Pointer to info_t structure.
 *@path: Path to the file to check.
 *
 *Return: 1 if the file exists, 0 otherwise.
 */
int isCmd(info_t *info, char *path)
{
	struct stat st;

	if (!info || !path)
	{
		return (0);
	}

	if (stat(path, &st))
	{
		return (0);
	}

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 *dupChars - Duplicate a portion of a string from start to stop.
 *
 *@pathstr: Input string to duplicate from.
 *@start: Start index for duplication.
 *@stop: Stop index for duplication.
 *
 *Return: Pointer to a duplicated string.
 */
char *dupChars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = start, k = 0;

	while (i < stop)
	{
		if (pathstr[i] != ':')
		{
			buf[k] = pathstr[i];
			k++;
		}

		i++;
	}

	buf[k] = '\0';

	return (buf);
}

/**
 *findPath - Find the full path to an executable file.
 *
 *@info: Pointer to info_t structure.
 *@pathstr: Path environment variable.
 *@cmd: Command to search for.
 *
 *Return: Pointer to the full path of the command if found, NULL otherwise.
 */
char *findPath(info_t *info, char *pathstr, char *cmd)
{
	char *path = NULL;
	int i = 0, curr_pos = 0;

	if (!pathstr)
	{
		return (NULL);
	}
	if (strLen(cmd) > 2 && startsWith(cmd, "./"))
	{
		if (isCmd(info, cmd))
		{
			return (cmd);
		}
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dupChars(pathstr, curr_pos, i);
			if (*path)
			{
				stringCat(path, "/");
			}

			stringCat(path, cmd);

			if (isCmd(info, path))
			{
				return (path);
			}

			if (!pathstr[i])
			{
				break;
			}
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
