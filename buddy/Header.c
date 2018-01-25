/*
 * Header.c
 *
 *  Created on: Nov 26, 2008
 *      Author: benr242
 */

#include <stdlib.h>
#include <stdio.h>
#include "include/Header.h"

void printHeader (HeaderPtr header)
{
	//printf("starting at --> %p ", header);
	if (header->tag == 1)
		printf("\t[%1d:%-10p:%p:%2d] \t(%p)\n", header->tag, header->linkf, header->linkb, header->kVal, header);
	else
		printf("\t[%1d:%-10p:%p:%2d] \t(%p)\n", header->tag, header->linkf, header->linkb, header->kVal, header);

}
