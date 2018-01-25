
#ifndef __NODE_H
#define __NODE_H

#include <stdio.h>
#include <stdlib.h>
#include "listhdr.h"
#include "Object.h"

typedef struct node Node;
typedef struct node * NodePtr;

struct node
{
	ObjectPtr obj;
	NodePtr next;
	NodePtr prev;
};

NodePtr createNode (ObjectPtr);
void freeNode(NodePtr, void (*freeObject)(void *));


#endif /* __NODE_H */
