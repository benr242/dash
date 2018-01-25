#include "../include/commands/Command.h"
#include "../include/commands/CompoundCommand.h"
#include "../include/Dash.h"

CompoundCommandPtr createCompoundCommand (char *str)
{
	const char *compound_delim = ";";

	char *mystr = (char *)mymalloc(sizeof(char)*(strlen(str)+1));
	strcpy(mystr, str);

	CompoundCommandPtr ccp = (CompoundCommandPtr)mymalloc(sizeof(CompoundCommand));
	ccp->count = 0;
	ccp->comStrs = (char **)mymalloc(sizeof(char *) * MAX_COMMANDS);
	ccp->commands = (CommandPtr *)mymalloc(sizeof(CommandPtr) * MAX_COMMANDS);
	char *com_str = (char *)mymalloc(sizeof(char)*MAX_COMMANDS);
	com_str = strtok(mystr, compound_delim);

	while (com_str)
	{
		ccp->comStrs[ccp->count] = (char *)mymalloc(sizeof(char)*(strlen(com_str)+1));
		strcpy(ccp->comStrs[ccp->count], com_str);
		ccp->count++;
		com_str = strtok(NULL, compound_delim);
	}

	int i = 0;
	while (i < ccp->count)
	{
		ccp->commands[i] = createCommand(ccp->comStrs[i]);
		i++;
	}

	return ccp;
}
