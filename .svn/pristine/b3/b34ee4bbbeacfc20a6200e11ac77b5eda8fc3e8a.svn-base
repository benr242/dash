/*
 * CompoundCommand.h
 *
 *  Created on: Dec 8, 2008
 *      Author: benr242
 */

#ifndef COMPOUNDCOMMAND_H_
#define COMPOUNDCOMMAND_H_

#define MAX_COMMANDS 10

typedef struct compoundCommand CompoundCommand;
typedef struct compoundCommand *CompoundCommandPtr;

struct compoundCommand
{
	int count;
	char **comStrs;
	CommandPtr *commands;
};

CompoundCommandPtr createCompoundCommand(char *);


#endif /* COMPOUNDCOMMAND_H_ */
