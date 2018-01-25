
#ifndef __JOB_H
#define __JOB_H

#include "../include/list/List.h"
#include "../include/commands/Command.h"

#define MAXJOBSTRING 128

typedef struct job Job;
typedef struct job *JobPtr;

struct job
{
	int key;
	CommandPtr command;
};

int *jobGetKey(void *);
char *jobToString(void *);
void jobFree(void *);
void jobMyFree(void *);
Boolean jobCompare(void *, void *);

Boolean jobCompareByKey(void *, void *);

JobPtr createJob (int key, CommandPtr command);
JobPtr toAnotherJob (JobPtr old);

void updateJobsStatus ();

#endif /* __JOB_H */
