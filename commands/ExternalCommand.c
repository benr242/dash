#include <sys/wait.h>
#include "../include/commands/Command.h"
#include "../include/Dash.h"

/*
 * fork, and wait if it's foreground, not if it's background
 */
int *executeExternal(CommandPtr command)
{
	pid_t pid;
	//pid_t pgid;
	//struct sigaction new_action, old_action;

	if ( (pid = fork()) < 0)
		printf("fork error\n");

	if (pid == 0) //child
	{
		*(command->pid) = getpid();
		setpgid(*(command->pid), *(command->pid)); //put it in its own group
		*(command->pgid) = getpgrp();
		//start executing the command if I'm the child
		execvp(command->executable, command->argList);
		exit(127);
	} else //parent
	{
		*(command->pid) = pid;

		JobPtr job = createJob(getNextJobId(), command);

		//if the child is a background job, add it to the list of bg jobs and do not wait for it
		if (command->isBackground)
		{
			addJobToList (getBgJobs(), job);

			if ((waitpid(*(command->pid), command->exitStatus, WUNTRACED | WNOHANG)) < 0)
				printf("waitpid error\n");

			printf("%s\n", jobToString(job));
		}
		//it is a foreground job, so I need to wait for it
		else
		{
			setFgJob(job);

			waitpid(*(command->pid), command->exitStatus, 0);
		}

	}

	return command->exitStatus;
}
