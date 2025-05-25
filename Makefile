CC=gcc
CFLAGS=-Wall -Wpedantic -std=c23

all: main
main: main.o quadtree.o
	$(CC) $(CFLAGS) -g -o main main.o quadtree.o

main.o: main.c quadtree.h
	$(CC) $(CFLAGS) -c main.c

quadtree.o: quadtree.c quadtree.h
	$(CC) $(CFLAGS) -c quadtree.c

clean:
	rm -f *.o main