CC=gcc
CFLAGS= -g -Wall
LFLAGS=-lpthread -lreadline -lncurses -llistlib
LIBDIR=-L. -Iinclude/list

progs=dash loop buddyTest
subdirs=commands dashMain test_progs buddy

COMMANDDIR=commands/

%.o: %.c
	$(CC) $(CFLAGS) $(LIBDIR) -c $<
	
all: $(subdirs) dash
	
dash: $(subdirs)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ dashMain/Dash.o dashMain/Job.o buddy/buddy.o buddy/Header.o $(LIBDIR) $(COMMANDDIR)*Command.o
	
dashMain:
	$(MAKE) -C dashMain

commands:
	$(MAKE) -C commands
	
test_progs:
	$(MAKE)	-C test_progs
	ln -sf test_progs/loop .
	ln -sf test_progs/buddyTest .
	
buddy:
	$(MAKE) -C buddy

vtest: commands dash
	valgrind --tool=memcheck --leak-check=yes dash
	
.PHONY: $(subdirs) clean
	
clean:
	rm -f *.[od] $(progs)
	$(MAKE) -C commands clean
	$(MAKE) -C dashMain clean
	$(MAKE) -C test_progs clean
	$(MAKE) -C buddy clean
	