
#include "../include/commands/Command.h"
#include 	"../include/Dash.h"

int *executeCd(CommandPtr command)
{
	static char *homeDir;
	Pw tmpPw;

	/* set the users home directory if it is not already */
	if (!homeDir)
	{
		tmpPw = getpwuid(getuid());
		homeDir = tmpPw->pw_dir;
	}

	/* the directory to change to, if it exists */
	char *dir;

	if (command->argCount == 2) /* change to dir */
	{
		dir = (char *) mymalloc (sizeof(char) * strlen(command->argList[1])+1);
		strcpy (dir, command->argList[1]);

		if (chdir(dir))
			printf("INVALID DIRECTORY\n");
	}
	else /* go home */
	{
		chdir(homeDir);
	}

	return command->pid;
}
