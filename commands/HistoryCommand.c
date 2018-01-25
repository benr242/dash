#include "../include/commands/Command.h"
#include "../include/Dash.h"

/*
 * HistoryCommand.c
 *
 *  Created on: Dec 8, 2008
 *      Author: benr242
 */

int *executeHistory (CommandPtr command)
{
	HIST_ENTRY **my_history = history_list();
	int i = 0;

	if (command->argCount == 2)
		i = where_history() - atoi(command->argList[1]);

	while (my_history[i])
		printf("[%d]: %s\n", i, my_history[i++]->line);

	return 0;
}
