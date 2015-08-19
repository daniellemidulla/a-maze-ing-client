#src.Makefile
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

# my project details
#LIBFLAG = -lcurl -lm
EXEC = maze
#OBJS = 
SRCS = AMStartup.c

# luckily, make has comments too!  

AMStartup: $(SRCS)
	$(CC) $(CFLAGS) -o maze $(SRCS) 


clean:
	rm -f *.o
	rm -f *.log
	rm -f *.a
