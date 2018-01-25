/*
 * header.h
 *
 *  Created on: Nov 26, 2008
 *      Author: benr242
 */

#ifndef HEADER_H_
#define HEADER_H_

typedef struct header Header;
typedef struct header * HeaderPtr;

void printHeader(HeaderPtr);

struct header
{
	int tag;
	HeaderPtr linkf;
	HeaderPtr linkb;
	int kVal;
};

#endif /* HEADER_H_ */
