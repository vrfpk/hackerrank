
CC = gcc
CFLAGS =
LDFLAGS =

all: main

main: main.o partition.o
	gcc $(LDFLAGS) -o $@ $^

partition.o: partition.c partition.h
	$(CC) $(CFLAGS) -o $@ -c $<

main.o: main.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm *.o main.exe
    
