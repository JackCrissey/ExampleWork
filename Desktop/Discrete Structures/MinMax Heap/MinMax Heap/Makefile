all: Driver.o MinMaxHeap.o
	g++ -Wall Driver.o MinMaxHeap.o -o output.out
run: 
	./output.out

val:
	valgrind ./output.out.

MinMaxHeap.o: MinMaxHeap.cpp
	g++ -Wall -c MinMaxHeap.cpp

Driver.o: Driver.cpp
	g++ -Wall -c Driver.cpp

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

