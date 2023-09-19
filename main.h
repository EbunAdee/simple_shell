#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdbool.h>

extern char **environ;

/**
 * struct programStatus - A structure to store program status information.
 * @name: The name of the program.
 * @cmd_count: The count of commands in the program.
 * @status: The status code of the program.
 *
 * This structure is used to store information about a program's status,
 * including its name, the count of commands, and the status code.
 */
struct programStatus
{
	char *name;
	int cmd_count;
	int status;
};
typedef struct programStatus program_t;

extern program_t prog;

char *getPathValue(const char *name);
int checkSlash(char *input);
char **processArguments(char *input, char *delimiter);
int checkBuiltin(char **argHolder, char *input);
void executeCommand(char **argArray, char *programName);
int printEnvironment(char **envHandler);
int exitProgram(char **argHolder, char *input);
char *modifyBuffer(char *command);
int checkCommand(char *command);
void handlePrompt(char *input, char *programName);
void printString(char *string);

void replaceVariables(char **args);
int checkAndExecuteBuiltins(char **args, char *input);
int checkAndExecuteCommand(char **args, char *programName);

#endif
