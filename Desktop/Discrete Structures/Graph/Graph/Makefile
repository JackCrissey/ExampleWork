all: Driver.o Graph.o
	g++ -Wall Driver.o Graph.o -o output.out
run: 
	./output.out

val:
	valgrind ./output.out.

Graph.o: Graph.cpp
	g++ -Wall -c Graph.cpp

Driver.o: Driver.cpp
	g++ -Wall -c Driver.cpp

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

