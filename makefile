CC = gcc
CFLAGS = -lpthread -Wall

all:read.o
	$(CC) -o run read.o $(CFLAGS)
read.o: read.c
	gcc -c read.c