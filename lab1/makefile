CC=gcc
CFLAGS=-Wall -std=c99 -g

all: format reverse_test
### Automatic variables
# $@ represents the name of the current rule’s target.
# $^ represents the names of all of the current rule’s dependencies, with spaces in between.
# {{{html}}}lt; represents the name of the current rule’s first dependency.

format: reverse.c test_reverse.c reverse.h
	clang-format -style=Google -i $^

reverse_test: test_reverse.o reverse.o reverse.h
	$(CC) $(CFLAGS) $^ -o $@

test_reverse.o: test_reverse.c
	$(CC) -c $^ -o $@

reverse.o: reverse.c
	$(CC) -c $^ -o $@

clean:
	rm -f reverse_test *.o