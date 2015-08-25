#src.Makefile
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

# my project details
#LIBFLAG = -lcurl -lm
GFLAG = -lncurses
TFLAG = -pthread
EXEC = maze
OBJS = AMStartup.o avatar.o graphics.o
SRCS = AMStartup.c avatar.c graphics.c

# luckily, make has comments too!  

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(TFLAG) $(GFLAG) -o $(EXEC) $(OBJS) 

AMStartup.o: AMStartup.c
	$(CC) $(CFLAGS) -c AMStartup.c

graphics.o: graphics.c
	$(CC) $(CFLAGS) -c graphics.c

clean:
	rm -f *.o
	rm -f *.log
	rm -f *.a
	rm -f $(EXEC)
