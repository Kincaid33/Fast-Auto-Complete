CC=gcc
CFLAGS=-I.
DEPS = autocomplete1.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

autocomplete1: autocomplete1.c
	gcc -o autocomplete1 autocomplete1.c insert.c -I.