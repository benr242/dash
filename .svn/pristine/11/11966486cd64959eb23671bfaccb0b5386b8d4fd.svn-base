#include "include/Buddy.h"
#include "include/Header.h"

const int CNUM_INTS = 10000;
const int MNUM_INTS = 150;

void **tests;

void runTests()
{
	const char *hamlet_mourning =
		" O that this too too solid flesh would melt, \n"
		" Thaw and resolve itself into a dew.\n"
		" Or that the Everlasting had not fix'd\n"
		" His canon 'gainst self-slaughter. O God! God!\n"
		" How weary, stale, flat, and unprofitable \n"
		" Seem to me all the uses of this world! \n"
		" Fie on't, ah fie, 'tis an unweeded garden \n"
		" That grows to seed; things rank and gross in nature \n"
		" Possess it merely. That it should come to this! \n"
		" But two months dead--nay, not so much, not two-- \n"
		" So excellent a king, that was to this \n"
		" Hyperion to a satyr, so loving to my mother \n"
		" That he might not beteem  the winds of heaven \n"
		" Visit her face to roughly. Heaven and earth, \n"
		" Must I remember? Why, she would would hang on him \n"
		" As if increase of appetite had grown \n"
		" By what it fed on; and yet within a month-- \n"
		" Let me not think on't--Frailty, thy name is woman-- \n"
		" A little month, or ere those shoes were old \n"
		" With which she follow'd my poor father's body, \n"
		" Like Niobe, all tears--why,she-- \n"
		" O God, a beast that wants discourse of reason \n"
		" Would have mourn'd longer--married my uncle, \n"
		" My father's brother--but no more like my father \n"
		" Than I to Hercules. Within a month, \n"
		" Ere yet the salt of unrighteous tears \n"
		" Had left the flushing in her galled eyes, \n"
		" She married--O most wicked speed! To post \n"
		" With such dexterity to incestuous sheets! \n"
		" It is not, nor it can not come to good. \n"
		" But, break my heart, for I must hold my tongue.\n";

	tests = mymalloc(1000);

	printf("mymallocing 64 (will be a 7 because of header size)\n");
	tests[0] = mymalloc(64);

	printf("mymallocing 100\n"); //a 7
	tests[1] = mymalloc(100);

	printf("mymallocing 64\n");
	tests[2] = mymalloc(64);

	//to force getting from higher level clearing out the 18's
	printf("mymallocing 131000\n");
	tests[3] = mymalloc(131000);
	tests[4] = mymalloc(131000);
	tests[5] = mymalloc(131000);
	myfree(tests[3]);

	tests[7] = mymalloc(16);

	//1400 chars: k == 11
	tests[6] = mymalloc(sizeof(char)*strlen(hamlet_mourning));
	strcpy(tests[6], hamlet_mourning);

	//for an NUM_INTS long array of ints
	tests[9] = (int **)mycalloc(CNUM_INTS, sizeof(int));
	int i;
	for (i = 0; i < CNUM_INTS; i++)
		((int *)tests[9])[i] = i;

	int **bigintarray = (int **)mymalloc(sizeof(int)*MNUM_INTS);
	for (i = 0; i < MNUM_INTS; i++)
		((int *)bigintarray)[i] = i;

	for (i = 0; i < CNUM_INTS; i++)
		printf("[%d] = %d, ", i, ((int *)tests[9])[i]);
	printf("\n");

	for (i = 0; i < MNUM_INTS; i++)
		printf("#%d# = %d \n", bigintarray[i], i);
	printf("\n");

	printBuddyLists();

	//print hamlet's mourning
	printf("%s\n", (char *)tests[6]);

	sleep (10);
	//system("clear");

	myfree(tests[0]);
	myfree(tests[1]);
	myfree(tests[2]);
	myfree(tests[4]);
	myfree(tests[5]);
	myfree(tests[6]);
	myfree(tests[7]);
	myfree(tests[9]);
	myfree(bigintarray);
	//now all have been freed

	myfree(tests);
}

int main (int argc, char *argv[])
{
	const size_t mByte = 1048576;
	size_t total = mByte*16;

	printf("test: %ld\n", (long int)total);

	initBuddySystem (total);

	runTests();

	printBuddyLists();
	baseCheck();

	return 0;
}
