#include	<sys/wait.h>
#include 	<signal.h>
#include 	"../include/commands/Command.h"
#include 	"../include/Dash.h"
#include	"../include/Job.h"

int *executeFg(CommandPtr command)
{
	ListPtr bgJobs = getBgJobs();
	ListPtr stJobs = getStJobs();

	int jobId;

	JobPtr toFg;
	if (!command->argList[1])
	{
		if (stJobs->size >= 1)
			jobId = stJobs->tail->obj->key;  //the most recently stopped job
		else
			jobId = -1;
	}
	else
		jobId = atoi(command->argList[1]);

	int *jobIdPtr = &jobId;

	//check background jobs
	NodePtr emptyNode;
	toFg = (JobPtr)(listSearch(bgJobs, &emptyNode, (void *)jobIdPtr));
	if (toFg)
	{
		moveBgToFg(toFg);
		//set 'new' fg job as controller
		setpgid(*(getFgJob()->command->pid), dash_pgrp_id);
		//tcsetpgrp(fd, *(getFgJob()->command->pgid));
		waitpid(*(getFgJob()->command->pid), getFgJob()->command->exitStatus, 0);
		signal(SIGINT, handle_signal);

		return command->pid;
	}

	//check stopped jobs
	toFg = (JobPtr)(listSearch(stJobs, &emptyNode, (void *)jobIdPtr));
	if (toFg)
	{
		moveStToFg(toFg);
		kill(*(toFg->command->pid), SIGCONT);
		//set 'new' fg job as controller
		//tcsetpgrp(fd, *(getFgJob()->command->pgid));
		waitpid(*(getFgJob()->command->pid), getFgJob()->command->exitStatus, 0);
		signal(SIGINT, handle_signal);

		return command->pid;
	}

	if (jobId == -1)
		return (int *)127;
	if (!toFg)
		printf("JobId %d was NOT found\n", *jobIdPtr);

	return 0;
}
