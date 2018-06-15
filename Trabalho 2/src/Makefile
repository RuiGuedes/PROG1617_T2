# Makefile

OBJS= Bus.o Shift.o Driver.o Line.o

all: main

main: $(OBJS) main.cpp
	g++ main.cpp -I. $(OBJS) -o busApp

Bus.o: Bus.cpp
	g++ -c Bus.cpp

Shift.o: Shift.cpp
	g++ -c Shift.cpp

Driver.o: Driver.cpp
	g++ -c Driver.cpp

Line.o: Line.cpp
	g++ -c Line.cpp


clean:
	rm -f busApp *.o

