CC = g++

all: clear source.bin play

source.bin: source.cpp
	$(CC) -o source.bin source.cpp -lncurses

clear:
	clear
play: 
	./source.bin
#all: prog.bin

#crat.o: crat.hpp crat.cpp
#	$(CC) -c -g -o crat.o crat.cpp

#prog.bin: crat.o prog.cpp
#	$(CC) -g -o prog.bin crat.o prog.cpp

clean:
	rm -rf *.o *.bin

