CC=gcc
CFLAGS= -g -Wall
LFLAGS=-1pthread -lreadline -lncurses
LIBDIR=-L. -Iinclude/list

%.o: %.c
	$(CC) $(CFLAGS) $(LIBDIR) -c $<
	
all: jobs dash

jobs: Job.o

dash: Dash.o
	
clean:
	rm -f *.o
