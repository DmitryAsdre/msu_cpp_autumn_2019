all: run
LinearAllocator.o: LinearAllocator.cpp LinearAllocator.hpp
	g++ -c -g LinearAllocator.cpp -o LinearAllocator.o
main.o : main.cpp 
	g++ main.cpp  -g -c -o main.o
main : main.o LinearAllocator.o
	g++ main.o LinearAllocator.o -o main
run : main 
	./main $(ARGS)
clean : 
	rm -rf main.o LinearAllocator.o main