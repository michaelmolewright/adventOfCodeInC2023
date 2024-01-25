CC=gcc
CFLAGS=-I.

VPATH = ../

out.o: main.o
	$(CC) -Wall -Werror -o day8.o main.o

%.o: %.c
	$(CC) -c -Wall -Werror -o $@ $<