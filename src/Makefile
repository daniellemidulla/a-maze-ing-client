#src.Makefile
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

# my project details
#LIBFLAG = -lcurl -lm
TFLAG = -pthread
EXEC = maze
OBJS = AMStartup.o avatar.o
SRCS = AMStartup.c avatar.c

# luckily, make has comments too!  

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(TFLAG) -o $(EXEC) $(OBJS) 

AMStartup.o: AMStartup.c
	$(CC) $(CFLAGS) -c AMStartup.c

clean:
	rm -f *.o
	rm -f *.log
	rm -f *.a
	rm -f $(EXEC)
