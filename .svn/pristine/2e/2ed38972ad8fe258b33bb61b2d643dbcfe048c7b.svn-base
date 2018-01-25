
#include "include/Buddy.h"
#include "include/Header.h"

static HeaderPtr *BLOCKS;
void *pool;
const int l = MIN_POWER, u = MAX_POWER;

int getK (size_t);
HeaderPtr findPrev (HeaderPtr, int);
HeaderPtr findNext (HeaderPtr, int);

void initBuddySystem (size_t total)
{
	pool = sbrk(total);

	//the only mallocs, for list heads
	int i;
	BLOCKS = (HeaderPtr *)malloc(sizeof(Header)*MAX_POWER);
	//set them all initially to NULL
	for (i=l; i<= u; i++)
	{
		BLOCKS[i] = (HeaderPtr)malloc(sizeof(Header));
		BLOCKS[i]->tag = 1;
		BLOCKS[i]->linkf = BLOCKS[i]->linkb = NULL;
	}

	int t = getK(total);
	BLOCKS[t]->linkf = (HeaderPtr)pool;

	HeaderPtr header;

	header = (HeaderPtr)BLOCKS[t]->linkf;
	header->tag = 1;
	header->linkf = 0;
	header->linkb = BLOCKS[t];
	BLOCKS[t]->linkb = header;
	header->kVal = t;
}

/* to show only the list headers, which aren't in "my" memory */
void baseCheck ()
{
	printf("-----------BASE------------\n");
	int i;
	for (i = u; i >= l; i--)
		//printf("BLOCKS[%2d] == %p:%p:%p\n", i, BLOCKS[i], BLOCKS[i]->linkf, BLOCKS[i]->linkb);
		printHeader(BLOCKS[i]);
	printf("-----------/BASE-----------\n");
}

void printBuddyLists()
{
	printf("-----------BLOCKS------------\n");
	int i;
	HeaderPtr header;
	for (i = u; i >= l; i--)
	{
		header = BLOCKS[i]->linkf;
		printf("BLOCKS[%2d] == \n", i);
		if (header)
		{
			while (header && (header->kVal == i))
			{
				printHeader(header);
				header = header->linkf;
			}
		}
	}
	printf("----------/BLOCKS-------------\n");
}

//total number of left shifts is the k val
int getK (size_t size)
{
	int k = MIN_POWER;
	long tmpSize = 1 << k;

	while (tmpSize < size)
	{
		tmpSize = tmpSize << 1;
		k++;
	}

	return k;
}

HeaderPtr buddy (HeaderPtr start)
{
	HeaderPtr buddy;

	long int buddyloc;
	//to use location relative to pool start
	long int skew = (long int)start-(long int)pool;
	int mask = 1 << start->kVal;
	buddyloc = skew ^ mask;

	//back to absolute location
	buddy = (HeaderPtr)(buddyloc+pool);

	return buddy;
}

//'to' is the level for this block to be split to
HeaderPtr split (HeaderPtr header, int to)
{
	int k = header->kVal - 1;

	header->linkb->linkf = header->linkf;
	if (header->linkf)
		header->linkf->linkb = header->linkb;

	HeaderPtr leftHeader = header;

	leftHeader->kVal = k;
	HeaderPtr rightHeader = buddy(leftHeader);

	//if this is the last on the level, make the head link back to here
	if (rightHeader > BLOCKS[k]->linkb)
		BLOCKS[k]->linkb = rightHeader;

	rightHeader->kVal = k;
	leftHeader->tag = rightHeader->tag = 1;
	leftHeader->linkf = rightHeader;

	HeaderPtr trace;
	trace = findPrev(rightHeader, k);

	//these are the first on the level
	if (!trace)
	{
		BLOCKS[k]->linkf = leftHeader;
		leftHeader->linkb = BLOCKS[k];
		leftHeader->linkf = rightHeader;
		rightHeader->linkf = NULL;
	}
	else
	{
		trace->linkf = leftHeader;
		leftHeader->linkb  = trace;

		trace = findNext(rightHeader, k);
		trace->linkb = rightHeader;

		if (rightHeader != trace)
			rightHeader->linkf = trace;
		else
			rightHeader->linkf = NULL;
	}

	rightHeader->linkb = leftHeader;

	if (k > to)
	{
		leftHeader->linkb->linkf = rightHeader;
		rightHeader->linkb = leftHeader->linkb;

		leftHeader = split(leftHeader, to);
	}

	return leftHeader;
}

//find the previous block on this level
HeaderPtr findPrev (HeaderPtr search, int level)
{
	HeaderPtr trace = BLOCKS[level]->linkf;

	if (!trace)
		trace = BLOCKS[level];
	else
		while ((trace->linkf) && (trace->linkf < search))
			trace = trace->linkf;

	return trace;
}

//find the next block on this level
HeaderPtr findNext (HeaderPtr search, int level)
{
	HeaderPtr trace = BLOCKS[level]->linkb;

	if (trace)
		while ((trace->linkb) && (trace->linkb > search))
			trace = trace->linkb;

	return trace;
}

//find the first available block of size >= startLevel
HeaderPtr findFirstAvail(int startLevel)
{
	HeaderPtr avail = BLOCKS[startLevel]->linkf;

	while (avail)
	{
		if (avail->tag == 1)
			break;

		avail = avail->linkf;
	}

	if (!avail)
		avail = findFirstAvail(startLevel+1);

	return avail;
}

void coalesce (HeaderPtr one, HeaderPtr two)
{
	int k = one->kVal+1;

	//swap them if 'one' is bigger
	HeaderPtr tmp;
	if (one > two)
	{
		tmp = one;
		one = two;
		two = tmp;
	}

	//fill in the gaps to be left behind
	one->linkb->linkf = two->linkf;
	if (two->linkf)
		two->linkf->linkb = one->linkb;

	if (BLOCKS[k-1]->linkb == two)
	{
		BLOCKS[k-1]->linkb = NULL;
		BLOCKS[k-1]->linkf = NULL;
	}

	//up to the next level
	one->kVal = two->kVal = k;

	//find the new links
	HeaderPtr prev = findPrev(one, k);

	one->linkf = prev->linkf;
	one->linkb = prev;
	prev->linkf = one;
	if (one->linkf)
		one->linkf->linkb = one;
	one->linkb->linkf = one;

	HeaderPtr bud = buddy(one);
	//keep going if the buddy is available
	if ((bud->tag == 1) && (one->kVal <= (MAX_POWER-1)))
		coalesce(one, bud);
}

void myfree(void *toFree)
{
	HeaderPtr free = (HeaderPtr)(toFree-sizeof(Header));
	free->tag = 1;

	HeaderPtr bud = buddy(free);

	//coalesce up, if buddy is also available
	if (bud->tag == 1)
		coalesce(free, bud);
}

void *mymalloc(size_t size)
{
	size_t newSize = size+sizeof(Header);
	int k = getK(newSize);

	//get the first available chunk
	HeaderPtr final;
	HeaderPtr first = findFirstAvail(k);

	//split it down to the correct size
	if (first->kVal > k)
		final = split(first, k);
	else
		final = first;

	final->tag = 0;

	return ++final;
}

void *mycalloc(size_t nmemb, size_t size)
{
	size_t total = nmemb*size;

	int *mem = (int *)mymalloc (total);

	//initialize to zero
	memset(mem, 0, (total-sizeof(Header)));

	return mem;
}
