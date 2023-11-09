#include "shell.h"

/**
 *getHistoryFile - Get the path to the history file
 *@info: Pointer to info_t struct containing environment information
 *
 *This function retrieves the path to the history file by appending HIST_FILE
 *to the HOME directory.
 *
 *Return: On success, returns a pointer to the history file path;
 *     on failure, returns NULL.
 */
char *getHistoryFile(info_t *info)
{
	char *dir, *buf;
	size_t bufSize;

	dir = getEnv(info, "HOME=");
	if (!dir)
	{
		return (NULL);
	}

	bufSize = strLen(dir) + strLen(HIST_FILE) + 2;
	buf = malloc(sizeof(char) * bufSize);

	if (!buf)
	{
		return (NULL);
	}

	buf[0] = '\0'; /*Using '\0' to represent an empty string */
	stringCpy(buf, dir);
	stringCat(buf, "/");
	stringCat(buf, HIST_FILE);

	return (buf);
}

/**
 *writeHistory - Write the history to a file
 *@info: Pointer to info_t struct containing history information
 *
 *This function writes the history entries stored in info to a file.
 *
 *Return: On success, returns 1; on failure, returns -1.
 */
int writeHistory(info_t *info)
{
	char *filename;
	int fd;
	list_t *node;

	filename = getHistoryFile(info);

	if (!filename)
	{
		return (-1);
	}

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
	{
		return (-1);
	}

	node = info->history;

	while (node)
	{
		putsFd(node->str, fd);
		putFd('\n', fd);
		node = node->next;
	}

	putFd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/**
 *readHistory - Read the history from a file
 *@info: Pointer to info_t struct for storing history
 *
 *This function reads the history entries from a file and populates info.
 *
 *Return: On success, returns the number of history entries read;
 *     on failure, returns 0.
 */
int readHistory(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getHistoryFile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			buildHistoryList(info, buf + last, linecount++);
			last = i + 1;
		}

	if (last != i)
		buildHistoryList(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);
	renumHistory(info);
	return (info->histcount);
}

/**
 *buildHistoryList - Build a history list from a buffer
 *@info: Pointer to info_t struct for storing history
 *@buf: Buffer containing history entries
 *@linecount: Number of history entries in the buffer
 *
 *This function builds a history list from a buffer of history entries.
 *
 *Return: Always returns 0.
 */
int buildHistoryList(info_t *info, char *buf, int linecount)
{
	list_t *result;
	list_t *node = NULL;

	if (info->history)
	{
		node = info->history;
	}

	result = addNodeEnd(&node, buf, linecount);

	if (!info->history)
	{
		info->history = result;
	}

	return (0);
}

/**
 *renumHistory - Renumber history entries
 *@info: Pointer to info_t struct containing history information
 *
 *This function renumbers the history entries in info.
 *
 *Return: The number of history entries after renumbering.
 */
int renumHistory(info_t *info)
{
	int i = 0;
	list_t *node = info->history;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	info->histcount = i;
	return (info->histcount);
}
