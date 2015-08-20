#test.Makefile
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

EXEC = maze_test
OBJS = maze_test.o maze.o
SRCS = maze_test.c

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

maze_test.o: maze_test.c ../src/maze.h
	$(CC) $(CFLAGS) -c maze_test.c

maze.o: ../src/maze.c ../src/maze.h
	$(CC) $(CFLAGS) -c ../src/maze.c

clean:
	rm -f *.o
	rm -f *.log
	rm -f $(EXEC)
