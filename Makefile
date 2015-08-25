#amazing.Makefile
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

SUBDIRS = src/ util/

maze: $(SUBDIRS)
	cd src/ && make maze

maze_test: $(SUBDIRS) test/*
	cd test/ && make maze_test

list_test: $(SUBDIRS) test/*
	cd test/ && make list_test

clean:
	cd src/; make clean
	cd util/; make clean
	cd test/; make clean
	rm -f *.o
	rm -f *.log
	rm -f *.a
