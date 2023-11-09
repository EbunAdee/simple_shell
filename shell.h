#ifndef _SHELL_H_
#define _SHELL_H_

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF_FLUSH -1
#define CMD_AND 2
#define CMD_CHAIN 3
#define CMD_NORM 0
#define CMD_OR 1
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096
#define READ_BUF_SIZE 1024
#define USE_STRTOK 0
#define USEgetLine 0
#define WRITE_BUF_SIZE 1024

extern char **environ;

/**
 *struct liststr - Structure for a linked list of strings.
 *@str: The string data.
 *@num: An associated number or identifier.
 *@next: Pointer to the next node in the list.
 */
typedef struct liststr
{
	char *str;
	int num;
	struct liststr *next;
} list_t;

/**
 *struct infoPass - Structure for passing information to functions.
 *@argv: An array of arguments.
 *@cmd_buf: An array of command buffers.
 *@environ: An array of environment variables.
 *@arg: A single argument.
 *@fname: A filename.
 *@path: A path.
 *@argc: The argument count.
 *@cmd_buf_type: Type of command buffer (CMD_NORM, CMD_AND, CMD_OR).
 *@env_changed: Flag indicating environment changes.
 *@err_num: Error number.
 *@histcount: History count.
 *@linecount_flag: Flag for counting lines.
 *@readfd: File descriptor for reading.
 *@status: Status indicator.
 *@alias: Pointer to a linked list of aliases.
 *@env: Pointer to a linked list of environment variables.
 *@history: Pointer to a linked list of command history.
 *@line_count: Line count.
 */
typedef struct infoPass
{
	char **argv;
	char *arg;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

/**
 *struct builtin - Structure for built-in commands and functions.
 *@type: The name of the built-in command.
 *@func: A pointer to the corresponding function for the command.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtinT;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

char **getEnviron(info_t *);
char **listToStrings(list_t *);
char **strTow(char *, char *);
char **strTow2(char *, char);
char *_strChr(char *, char);
char *_strnCat(char *dest, const char *src, int n);
char *_strnCpy(char *, char *, int);
char *convertNum(long int, int, int);
char *dupChars(char *, int, int);
char *findEnv(list_t *env, const char *name);
char *findPath(info_t *, char *, char *);
char *getEnv(info_t *, const char *);
char *getHistoryFile(info_t *info);
char *memSet(char *, char, unsigned int);
char *startsWith(const char *, const char *);
char *stringCat(char *, char *);
char *stringCpy(char *, const char *);
char *stringDup(const char *);
int bFree(void **);
int buildHistoryList(info_t *info, char *buf, int linecount);
int deleteNodeAtIndex(list_t **, unsigned int);
int ePutChar(char);
int errAtoi(char *);
int findBuiltin(info_t *);
int getLine(info_t *, char **, size_t *);
int hsh(info_t *, char **);
int interact(info_t *);
int isAlpha(int);
int isChain(info_t *, char *, size_t *);
int isCmd(info_t *, char *);
int isDelim(char c, const char *delim);
int loopHsh(char **);
int myAlias(info_t *);
int myCd(info_t *);
int myEnv(info_t *);
int myExit(info_t *);
int myHelp(info_t *);
int myHistory(info_t *);
int mySetEnv(info_t *);
int myUnsetEnv(info_t *);
int popuEnvList(info_t *);
int printD(int, int);
int putChar(char);
int putFd(char c, int fd);
int putsFd(char *str, int fd);
int readHistory(info_t *info);
int renumHistory(info_t *info);
int replaceAlias(info_t *);
int replaceString(char **, char *);
int replaceVars(info_t *);
int setCustomEnv(list_t **env, const char *name, const char *value);
int SetEnv(info_t *, char *, char *);
int shAtoi(const char *);
int stringCmp(char *, char *);
int strLen(char *);
int unsetCustomEnv(list_t **env, const char *name);
int unSetEnv(info_t *, char *);
int writeHistory(info_t *info);
list_t *addNode(list_t **, const char *, int);
list_t *addNodeEnd(list_t **, const char *, int);
list_t *nodeStartsWith(list_t *, char *, char);
size_t listLen(const list_t *);
size_t printList(const list_t *);
size_t printListStr(const list_t *);
ssize_t getInput(info_t *);
ssize_t getNodeIndex(list_t *, list_t *);
void *reAlloc(void *, unsigned int, unsigned int);
void _puts(char *);
void checkChain(info_t *, char *, size_t *, size_t, size_t);
void clearInfo(info_t *);
void ePuts(char *);
void fFree(char **);
void findCmd(info_t *);
void forkCmd(info_t *);
void freeInfo(info_t *, int);
void freeList(list_t **);
void printError(info_t *, char *);
void removeComm(char *);
void setInfo(info_t *, char **);
void sigintHandler(int);

#endif
