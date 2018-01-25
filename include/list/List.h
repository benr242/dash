#ifndef __LIST_H
#define __LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "listhdr.h"
#include "Node.h"
#include "Object.h"

typedef struct list List;
typedef struct list * ListPtr;

struct list
{
	int size;
	NodePtr head;
	NodePtr tail;

	//pointers to functions
	int *(*getKey)(void *);
	char *(*toString)(void *);
	void (*freeObject)(void *);
    Boolean (*compare)(void *, void *);
    void *(*search)(void *, void *);
};

/* prototypes of public methods */

ListPtr createList(int *(*getKey)(void *), char *(*toString)(void *),
		void (*freeObject)(void *), Boolean (*compare)(void *, void *)); /* constructor */

void freeList(ListPtr); /* destructor */

int getListSize(ListPtr);

Boolean isEmpty(ListPtr);

void addAtFront(ListPtr, NodePtr);
void addAtRear(ListPtr, NodePtr);

void removeFront(ListPtr);
void removeRear(ListPtr);
//void removeNode(ListPtr, NodePtr);
void *removeListObject(ListPtr, void *);

void *listSearch(ListPtr, NodePtr *, void *);
int listGetMax(ListPtr);

void reverseList(ListPtr);

void printList(ListPtr);


#endif /* __LIST_H */
