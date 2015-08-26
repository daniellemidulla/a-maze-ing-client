#src.Makefile
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

# my project details
#LIBFLAG = -lcurl -lm
GFLAG = -lncurses
TFLAG = -pthread
EXEC = maze
OBJS = AMStartup.o avatar.o
SRCS = AMStartup.c avatar.c 

# luckily, make has comments too!  

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(TFLAG) $(GFLAG) -o $(EXEC) $(OBJS) 

#graphics.o: graphics.c
#	$(CC) $(CFLAGS) -c graphics.c

clean:
	rm -f *.o
	rm -f *.log
	rm -f *.a
	rm -f $(EXEC)
