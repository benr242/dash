CC=gcc
CFLAGS= -g -Wall
LIBDIR=-lm

%.o: %.c
	$(CC) $(CFLAGS) -c $<
	
all: buddy.o buddyTest

buddy.o: Buddy.c Header.o
	$(CC) $(CFLAGS) $(LIBDIR) Buddy.c -o buddy.o -c

buddyTest: buddy.o buddyTest.c
	$(CC) $(CFLAGS) buddy.o Header.o buddyTest.c -o buddyTest
	cp buddyTest ../test_progs

.PHONY: clean

	
clean:
	rm -f *.[od] buddyTest
