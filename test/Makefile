#test.Makefile
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

MAZE_EXEC = maze_test
MAZE_OBJS = maze_test.o maze.o
MAZE_SRCS = maze_test.c

LIST_EXEC = list_test
LIST_OBJS = list_test.o list.o
LIST_SRCS = list.c

$(MAZE_EXEC): $(MAZE_OBJS)
	$(CC) $(CFLAGS) -o $(MAZE_EXEC) $(MAZE_OBJS)

maze_test.o: maze_test.c
	$(CC) $(CFLAGS) -c maze_test.c

maze.o: ../src/maze.c ../src/maze.h
	$(CC) $(CFLAGS) -c ../src/maze.c

$(LIST_EXEC): $(LIST_OBJS)
	$(CC) $(CFLAGS) -o $(LIST_EXEC) $(LIST_OBJS)

list_test.o: list_test.c
	$(CC) $(CFLAGS) -c list_test.c

list.o: ../src/list.c ../src/list.h
	$(CC) $(CFLAGS) -c ../src/list.c

clean:
	rm -f *.o
	rm -f *.log
	rm -f $(MAZE_EXEC)
	rm -f $(LIST_EXEC)
