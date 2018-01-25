
#include "../include/Dash.h"
#include "../include/Job.h"

/* -------------------FUNCTIONS FOR THE LIST--------------------------------- */
int *jobGetKey(void *obj)
{
	JobPtr jp = (JobPtr)obj;
	return &(jp->key);
}

char *jobToString(void *obj)
{
	JobPtr job = (JobPtr)obj;
	CommandPtr command = job->command;

	char *commandOutput = commandToString(command);
	char *output = (char *)mymalloc(sizeof(int) + (sizeof(char)*(strlen(commandOutput)+ 1)));
	sprintf(output, "[%d] %s", job->key, commandOutput);
	return output;
}

void jobFree (void *obj)
{
	JobPtr job = (JobPtr)obj;
	myfree(job->command);
}

/* compare JobPtr->key with an int */
Boolean jobCompareByKey(void *obj, void *vkey)
{
	JobPtr job = (JobPtr)obj;
	int *key = (int *)vkey;

	if (job->key == *key)
		return TRUE;
	else
		return FALSE;
}

/* both objects should be JobPtrs */
Boolean jobCompare(void *obj1, void *obj2)
{
	JobPtr job1 = (JobPtr)obj1;
	JobPtr job2 = (JobPtr)obj2;

	if (job1->key == job2->key)
		return TRUE;
	else
		return FALSE;
}

void updateJobsStatus (ListPtr bgJobs)
{
	NodePtr node = bgJobs->head;
	JobPtr job;
	CommandPtr command;

	//to clean up after a zombie
	if((job = getFgJob()))
	{
		waitpid(*(job->command->pid), NULL, WNOHANG);
		jobFree(job);
		setFgJob(NULL);
	}

	while (node)
	{
		job = (JobPtr)node->obj->data;
		command = job->command;
		*(command->exitStatus) = waitpid(*(command->pid), command->exitStatus, WUNTRACED | WNOHANG);

		if (*(command->exitStatus) != 0) //either an error, or it finished
		{
			printf("%s Done\n", jobToString(job));
			jobFree(job);
			removeListObject(bgJobs, (JobPtr)node->obj->data);
		}
		node = node->next;
	}
}

JobPtr createJob (int key, CommandPtr command)
{
	JobPtr newJob = (JobPtr) mymalloc (sizeof(Job));
	newJob->key = key;
	newJob->command = command;

	return newJob;
}

