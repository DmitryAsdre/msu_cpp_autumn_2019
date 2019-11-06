vector.o : Vector.hpp Vector.cpp
	g++ -c Vector.cpp -o vector.o
main.o : main.cpp
	g++ -c main.cpp -o main.o
main : main.o Vector.o
	g++ main.o Vector.o -o main