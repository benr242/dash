#include	<sys/wait.h>
#include 	"../include/commands/Command.h"
#include 	"../include/Dash.h"

int *executeJobs(CommandPtr command)
{
	updateJobsStatus(getBgJobs());

	printJobs();
	return 0;
}
