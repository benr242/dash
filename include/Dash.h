
#ifndef	__DASH_H
#define	__DASH_H

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "list/List.h"
#include "Job.h"
#include "commands/Command.h"
#include "commands/CompoundCommand.h"
#include "dashhdr.h"
#include "../buddy/include/Buddy.h"
#include "../buddy/include/Header.h"

#define	MAXLINE	4096

const char *dashPrompt;
Pw tmpPw;

pid_t dash_pid;
pid_t dash_pgrp_id;

struct sigaction new_action, old_action, query_action;

JobPtr fgJob;
ListPtr bgJobs; //jobs running in the background
ListPtr stJobs; //stopped jobs

int ofd, fd;

void using_history();

void handle_signal (int sig);

int getDashPid ();
void setPrompt ();
void setFgJob (JobPtr);
void addJobToList(ListPtr, JobPtr);
void addStJob(JobPtr);
int getJobCount(Boolean);
int getNextJobId();
JobPtr getFgJob ();
JobPtr getBgJob (void *);
ListPtr getBgJobs ();
ListPtr getStJobs ();

Boolean moveBgToFg (JobPtr node);
Boolean moveStToFg (JobPtr);
Boolean moveStToBg (JobPtr);
void moveFgToSt (JobPtr);

void printJobs ();

#endif /* __DASH_H */
