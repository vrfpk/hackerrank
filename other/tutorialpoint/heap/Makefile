
OBJS = \
	main.o\

CC = gcc
CFLAGS = -O2 -Wall
CXX = g++
CXXFLAGS = -O2
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
    
