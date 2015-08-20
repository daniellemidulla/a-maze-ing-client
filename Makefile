#amazing.Makefile
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

SUBDIRS = src/ util/

.PHONY: maze test

maze: $(SUBDIRS)
	cd src/ && make maze

test: $(SUBDIRS) test/*
	cd test/ && make maze_test

clean:
	cd src/; make clean
	cd util/; make clean
	cd test/; make clean
	rm -f *.o
	rm -f *.log
	rm -f *.a
