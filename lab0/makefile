CC=gcc
CFLAGS=-Wall -std=c99 -g

all: hello_world

hello_world: hello_world.c
	$(CC) $(CFLAGS) -o hello_world hello_world.c
	./hello_world

clean:
	rm hello_world