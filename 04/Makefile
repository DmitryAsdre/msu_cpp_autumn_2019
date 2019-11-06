vector.o : Vector.hpp Vector.cpp
	g++ -c Vector.cpp -o vector.o
main.o : main.cpp
	g++ -c main.cpp -o main.o
bigint.o : BigInt.hpp BigInt.cpp
	g++ -c BigInt.cpp -o bigint.o
main : main.o Vector.o bigint.o
	g++ main.o Vector.o bigint.o -o main