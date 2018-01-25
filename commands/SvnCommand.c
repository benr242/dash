#include "../include/commands/Command.h"
#include "../include/Dash.h"

/* do not fork, just return */
int *executeSvn(CommandPtr command)
{
	//show subversion info
	system("svn info");

	exit(127);
}
