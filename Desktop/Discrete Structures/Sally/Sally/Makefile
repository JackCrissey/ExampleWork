all: driver2.o Sally.o
	g++ -Wall driver2.o Sally.o -o output.out
run: 
	./output.out

val:
	valgrind ./output.out.

Sally.o: Sally.cpp
	g++ -Wall -c Sally.cpp

driver2.o: driver2.cpp
	g++ -Wall -c driver2.cpp

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

