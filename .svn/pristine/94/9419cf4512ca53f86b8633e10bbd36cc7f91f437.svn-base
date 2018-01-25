#include	<sys/wait.h>
#include 	"../include/commands/Command.h"
#include 	"../include/Dash.h"

/* do not fork, just exit */
int *executeTerminate(CommandPtr command)
{
	freeList(bgJobs);
	freeList(stJobs);

	//exit from dash
	exit(127);
}
