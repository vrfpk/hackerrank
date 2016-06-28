
OBJS = \
	main.o\
	square_subsequences.o\
	repair_roads.o\
	repair_roads2.o\
	max_partition.o\

CC = gcc
CFLAGS = -O2 -Wall -D DEBUG
CXX = g++
CXXFLAGS = -O2 -Wall
LD = g++
# gcc
LDFLAGS =

all: main.exe

main.exe: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	
.PHONY: clean

clean:
	rm *.o *.exe*
    
