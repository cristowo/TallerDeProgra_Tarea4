FLAGS = -g

all: test_MaxFlujo test_ToThink main

main: main.cpp MaxFlujo.o ToThink.o
	g++ ${FLAGS} main.cpp -o main MaxFlujo.o ToThink.o

test_MaxFlujo: MaxFlujo.o test_MaxFlujo.cpp
	g++ ${FLAGS} MaxFlujo.o test_MaxFlujo.cpp -o test_MaxFlujo

MaxFlujo.o: MaxFlujo.cpp MaxFlujo.h
	g++ -c MaxFlujo.cpp

test_ToThink: ToThink.o test_ToThink.cpp MaxFlujo.o
	g++ ${FLAGS} ToThink.o test_ToThink.cpp -o test_ToThink MaxFlujo.o

ToThink.o: ToThink.cpp ToThink.h
	g++ -c ToThink.cpp

clear:
	rm -f *.o test_MaxFlujo test_ToThink main

run_all: all
	./test_MaxFlujo ./test_ToThink ./main