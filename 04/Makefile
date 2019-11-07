vector.o : Vector.hpp Vector.cpp
	g++ -c -g Vector.cpp -o vector.o
main.o : main.cpp
	g++ -c -g main.cpp -o main.o
bigint.o : BigInt.hpp BigInt.cpp
	g++ -c -g BigInt.cpp -o bigint.o
main : main.o Vector.o bigint.o
	g++ -g main.o Vector.o bigint.o -o main
clean : 
	rm -rf main.o main bigint.o vector.o