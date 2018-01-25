#include	<sys/wait.h>
#include 	"../include/commands/Command.h"
#include 	"../include/Dash.h"

//need the tcsetpgrp for this

int *executeBg(CommandPtr command)
{
	ListPtr stJobs = getStJobs();
	NodePtr emptyNode;
	JobPtr toBg;
	int jobId;
	if (!command->argList[1])
	{
		if (stJobs->size >= 1)
			jobId = stJobs->tail->obj->key;
		else
			jobId = -1;
	}
	else
		jobId = atoi(command->argList[1]);

	int *jobIdPtr = &jobId;

	toBg = (JobPtr)(listSearch(stJobs, &emptyNode, (void *)jobIdPtr));
	if (toBg)
	{
		moveStToBg(toBg);
		kill(*(toBg->command->pid), SIGCONT);

		if ((waitpid(*(toBg->command->pid), command->exitStatus, WNOHANG)) < 0)
			printf("waitpid error\n");

		//signal(SIGINT, handle_signal);

		return command->exitStatus;
	}

	if (jobId == -1)
		return (int *)127;
	if (!toBg)
		printf("JobId %d was NOT found\n", *jobIdPtr);

	return command->pid;
}
