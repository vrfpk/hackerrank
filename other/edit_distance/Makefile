
OBJS = main.o

CC = gcc
CFLAGS = -O2 -std=c11 -Wall
CXX = g++
CXXFLAGS = -O2 -std=c++11 -Wall
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
    
