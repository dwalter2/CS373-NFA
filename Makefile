walters_p1: walters_p1.o
	g++ walters_p1.o -o walters_p1
walters_p1.o: walters_p1.cpp
	g++ -c walters_p1.cpp
run: walters_p1
	./walters_p1 machine1.txt 01010101010101010101000000000000
clean: walters_p1
	rm -rf *.o walters_p1
