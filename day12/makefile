CC=gcc
CFLAGS=-I.

VPATH = ../

out.o: main.o helper.o
	$(CC) -Wall -Werror -o day8.o main.o helper.o

%.o: %.c
	$(CC) -c -Wall -Werror -o $@ $<