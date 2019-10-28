main.o : main.cpp 
	g++ -c main.cpp -o main.o
Matrix.o : Matrix.cpp Matrix.hpp
	g++ -c Matrix.cpp -o Matrix.o
main: main.o Matrix.o
	g++ main.o Matrix.o -o main
	