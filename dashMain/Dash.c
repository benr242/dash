
#include "../include/dashhdr.h"
#include "../include/Dash.h"

const size_t megaByte = 1048576;

/* set prompt to the BASH_PROMPT environment variable if it exists
 * '[bash]$' otherwise
 */
void setPrompt ()
{
	if ((dashPrompt = getenv("DASH_PROMPT")) == 0)
		dashPrompt = "[ben's dash]$ ";
}

int getDashPid ()
{
	return dash_pid;
}

void setFgJob (JobPtr job)
{
	fgJob = job;
}

void addJobToList(ListPtr list, JobPtr job)
{
	addAtRear(list, createNode(createObject(job->key, job)));
}

JobPtr getFgJob ()
{
	return fgJob;
}

ListPtr getBgJobs ()
{
	return bgJobs;
}

ListPtr getStJobs ()
{
	return stJobs;
}

int getNextJobId ()
{
	int nextBg = 0, nextSt = 0, next;
	nextBg = listGetMax(bgJobs);
	nextSt = listGetMax(stJobs);

	if (nextSt < nextBg)
		next = nextBg;
	else
		next = nextSt;

	next++;

	return next;
}

void printJobs ()
{
	ListPtr list = getStJobs();
	if (list->size > 0)
		printf("STOPPED JOBS [%d]\n", list->size);
	printList(list);

	list = getBgJobs();
	if (list->size > 0)
		printf("BACKGROUND JOBS [%d]\n", list->size);
	printList(list);
}

Boolean moveBgToFg (JobPtr job)
{
	ListPtr bgJobs = getBgJobs();
	void *tmp = removeListObject(bgJobs, job);

	if (tmp)
	{
		fgJob = (JobPtr)(tmp);
		return TRUE;
	}
	return FALSE;
}

Boolean moveStToFg (JobPtr job)
{
	ListPtr stJobs = getStJobs();
	void *tmp = removeListObject(stJobs, job);

	if (tmp)
	{
		fgJob = (JobPtr)(tmp);
		return TRUE;
	}
	return FALSE;
}

Boolean moveStToBg (JobPtr job)
{
	void *tmp = removeListObject(getStJobs(), job);

	if (tmp)
	{
		addJobToList(getBgJobs(), tmp);
		return TRUE;
	}
	return FALSE;
}

void moveFgToSt (JobPtr job)
{
	JobPtr exFg = getFgJob();
	addJobToList(getStJobs(), exFg);

	fgJob = NULL;
}

jmp_buf loop;

int main (int argc, char *argv[])
{
	//just execute a special command, skipping the rest,
	//if the args (e.g. "-v") say to
	if (argc > 1)
	{
		if (strcmp(argv[1], "-v") == 0)
		{
			system("svn info");
			exit(0);
		}
	}

	initBuddySystem(megaByte*16);

	fd = open("/dev/tty", O_RDWR);
	dash_pgrp_id = (pid_t)mymalloc(sizeof(pid_t));
	dash_pgrp_id = getpgrp();

	int code;

	new_action.sa_handler = handle_signal;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;

	sigaction(SIGINT, NULL, &old_action);	//store current action in old_action.sa_handler
	if (old_action.sa_handler != SIG_IGN)	//if it wasn't ignored previously, set it to what i want
		sigaction (SIGINT, &new_action, NULL);
	sigaction(SIGTSTP, NULL, &old_action);
	if (old_action.sa_handler != SIG_IGN)
		sigaction (SIGTSTP, &new_action, NULL);

	fgJob = NULL;
	bgJobs = createList(jobGetKey, jobToString, jobFree, jobCompareByKey);
	stJobs = createList(jobGetKey, jobToString, jobFree, jobCompareByKey);

	setPrompt();

	using_history();
	char *commStr;

	char *buf;
	code = sigsetjmp(loop, 1);

	while ((buf = readline(dashPrompt)))
	{
		commStr = (char *)mymalloc(sizeof(char)*(strlen(buf)+1));
		strcpy(commStr, buf);
		free (buf);

		if ((strlen(commStr) > 1)&&(strcmp("history", commStr))) //don't need it in history if it's a NULL or history 	command
			add_history(commStr);

		CompoundCommandPtr ccomm = createCompoundCommand(commStr);

		int i = 0;
		while (i < ccomm->count)
		{
			ccomm->commands[i]->executeFunction(ccomm->commands[i]);
			i++;
		}

		updateJobsStatus(bgJobs);
	}

	exit(0);
}

/* handle SIGINT and SIGTSTP signals that are caught
 * children will not have caught them initially
 */
void handle_signal(int sig)
{
  	switch(sig)
  	{
    	case SIGINT: //Ctl-c
		if (fgJob)
    		{
    			kill(*(fgJob->command->pid), SIGINT);
    		} else
    			printf("Caught signal SIGINT\n");
			break;
		case SIGTSTP: //Ctl-z
			if (fgJob)
			{
				printf("[%d]+ Stopped\n", fgJob->key);
    				kill(*(fgJob->command->pid), SIGTSTP);
    				moveFgToSt(fgJob);

			} else
				printf("Caught signal SIGTSTP\n");
			break;
		default:
			break;
	}
	fflush(stdout);
	siglongjmp(loop, 1);
}
