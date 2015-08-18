#amazing.Makefile
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

SUBDIRS = src/ util/

clean:
	cd src/; make clean
	cd util/; make clean
	rm -f *.o
	rm -f *.log
	rm -f *.a
