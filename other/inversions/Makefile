
CC = gcc
CFLAGS =
LDFLAGS =

all: main

main: main.o inversions.o
	gcc $(LDFLAGS) -o $@ $^

inversions.o: inversions.c inversions.h
	$(CC) $(CFLAGS) -o $@ -c $<

main.o: main.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm *.o main.exe
    
