all: walters_p1.o
	g++ walters_p1.o -o walters_p1
walters_p1.o: walters_p1.cpp
	g++ -c walters_p1.cpp
run: all
	./walters_p1 testinput.txt 101010101010101010101010101010101010
