walters_p1: walters_p1.o
	g++ walters_p1.o -o walters_p1
walters_p1.o: walters_p1.cpp
	g++ -c walters_p1.cpp
run: walters_p1
	./walters_p1 testinput.txt 1010101010101010101010101010101010100
clean: walters_p1
	rm -rf *.o walters_p1
