#ifndef __COMMAND_H
#define __COMMAND_H

#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include "../dashhdr.h"

#define MAXARGSIZE 16
#define MAXARGS 8

typedef struct passwd *Pw;

typedef struct command Command;
typedef struct command *CommandPtr;
typedef char **ArgumentList;

pid_t commandPid;
pid_t commandParentPid;
pid_t commandGrpPid;

struct command
{
	int *pid;
	int *pgid;
	int *jobId;
	char *executable;
	ArgumentList argList;
	int argCount;
	boolean isBackground;
	int *exitStatus;

	int *(*executeFunction)(CommandPtr);
	char *(*toString)(CommandPtr);
};

CommandPtr createCommand(char *);
char *commandToString(CommandPtr);
char *getStatusString (CommandPtr);

char *getExecutable(char *);
void setExecutable(CommandPtr, char *);
char **getArgs(CommandPtr, char *);
int getArgListSize(CommandPtr);
void setArgList(CommandPtr, char *);
Boolean getIsBackground(CommandPtr);
int *(*getExecuteFunction(CommandPtr, char *))(CommandPtr);

/* built in commands */
int *executeNull(CommandPtr);
int *executeTerminate(CommandPtr);
int *executeCd(CommandPtr);
int *executeJobs(CommandPtr);
int *executeHistory(CommandPtr);
int *executeFg(CommandPtr);
int *executeBg(CommandPtr);
int *executeSvn(CommandPtr);

/* external commands */
int *executeExternal(CommandPtr);

#endif /*__COMMAND_H*/

