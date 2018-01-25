#include 	"../include/commands/Command.h"
#include 	"../include/Dash.h"

pid_t	pid;
int		status;
const char *delimiters = " "; /* ' ' to separate args, and '|' in case piping comes later */

/*
 * allocate space for new Command object, and run through a
 * series of functions to set the values of it
 */
CommandPtr createCommand (char *str)
{
	CommandPtr command = (CommandPtr) mymalloc(sizeof(Command));

	if (strlen(str) == 0) //the rest of the function is irrelevant
	{
		command->executeFunction = executeNull;
		return command;
	}
	command->pid = (pid_t *) mymalloc (sizeof (pid_t));
	command->pgid = (pid_t *) mymalloc (sizeof (pid_t));
	command->exitStatus = (int *) mymalloc (sizeof (int));
	*(command->exitStatus) = 0;
	command->executable = getExecutable(str);
	command->argList = getArgs(command, str);
  	command->isBackground = getIsBackground(command);
  	command->executeFunction = getExecuteFunction(command, str);
  	command->toString = commandToString;

	return command;
}

char *commandToString(CommandPtr command)
{
	int l = 0, i;
	l = (strlen(command->argList[0]) + 1);
	for (i=0; i < command->argCount; i++)
		l += (strlen(command->argList[i]) + 1);

	char *output = (char *)mymalloc(sizeof(char)*l);
	strcpy(output, command->argList[0]);

	for (i = 1; i < command->argCount; i++)
		sprintf(output, "%s %s", output, command->argList[i]);

	return output;
}

char *getExecutable(char *str)
{
	char *exec;
	char *tmpExec;
	tmpExec = strtok(str, delimiters);
	if (tmpExec)	//should always be true
	{
		exec = (char *)mymalloc(sizeof(char)*strlen(tmpExec));
		exec = tmpExec;
	}
	return exec;
}

char **getArgs(CommandPtr command, char *str)
{
	char **args; //the var that will actually be assigned to the command
	int i = 0;

	args = (char **)mymalloc(sizeof(char)*MAXARGS);
	//the first arg

	args[i] = (char *)mymalloc(sizeof(char)*strlen(command->executable));

	char *arg= command->executable;


	strcpy(args[i], arg);
	command->argCount = ++i;


	//fill in the rest of the args
	arg = strtok(NULL, delimiters);
	while (arg)
 	{
		args[i] = (char *) mymalloc(sizeof(char)*strlen(arg)+1);
		args[i] = arg;
		command->argCount = ++i;
		arg = strtok(NULL, delimiters);
 	}

	args[command->argCount] = NULL;

	return args;
}

int *(*getExecuteFunction(CommandPtr command, char *str))(CommandPtr com)
{
		/* set execute function to do nothing if no command was entered */
		if (*str == '\0')
			return executeNull;

		/* set execute function to quit if command is 'exit' or 'logout' */
		char *firstArg = command->argList[0];
		if ((!strcmp(firstArg, "exit")) || (!strcmp(firstArg, "logout")))
			return executeTerminate;

		/* set execute function to cd execute if appropriate */
		if (!strcmp(firstArg, "cd"))
			return executeCd;

		/* set execute funtion to job */
		if (!strcmp(firstArg, "jobs"))
			return executeJobs;

		if (!strcmp(firstArg, "history"))
			return executeHistory;

		if (!strcmp(firstArg, "fg"))
			return executeFg;

		if (!strcmp(firstArg, "bg"))
			return executeBg;

		/* show subversion info, then exit */
		if (!strcmp(firstArg, "-v"))
			return executeSvn;

		/* execute external commnand */
		return executeExternal;

	return 0;
}

/* return true if the last arg is, or ends with, a & */
Boolean getIsBackground(CommandPtr command)
{
	Boolean isBg = FALSE;
	char *amp = "&";	//to compare with later

	/* pointer to the last argument given */
	char *lastArg = command->argList[command->argCount - 1];

	/* if the last argument IS an &, remove it from the argList and set isBg to TRUE */
 	if ((strcmp(lastArg, amp) == 0))
 	{
 		command->argList[command->argCount - 1] = NULL;
 		command->argCount--;
 		return TRUE;
 	}


 	/* if the last argument ends with an &, remove the & from the argument and set isBg to TRUE */
 	while (*lastArg++ != '\0')
		;
	lastArg -= 2;
	if ((strcmp(lastArg, amp) == 0))
	{
		*lastArg = 0;
		isBg = TRUE;
	}


	//trim the executable, if it ends with a '&'
	char *exec = command->executable;
 	while (*exec++ != '\0')
		;
	exec -= 2;
	if ((strcmp(exec, amp) == 0))
	{
		*exec = 0;
		isBg = TRUE;
	}

	return isBg;
}


