CC=gcc
CFLAGS= -g -Wall
LFLAGS=-1pthread -lreadline -lncurses
LIBDIR=-L. -Iinclude/list

COMMANDS=NullCommand.o TerminateCommand.o CdCommand.o JobsCommand.o HistoryCommand.o \
	SvnCommand.o BgCommand.o FgCommand.o ExternalCommand.o CompoundCommand.o

all: commands

commands: $(COMMANDS) Command.o
	
Command.o: Command.c ../include/commands/Command.h
	$(CC) $(CFLAGS) -c -o $@ Command.c

%Command.o: %Command.c Command.h
	$(CC) $(CFLAGS) $(LIBDIR) -c -o $@ $*Command.c
	
clean:
	rm -f *.o
