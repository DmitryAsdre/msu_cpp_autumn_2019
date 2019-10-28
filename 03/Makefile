main.o : main.cpp 
	g++ -c main.cpp -o main.o
Matrix.o : Matrix.cpp Matrix.hpp
	g++ -c Matrix.cpp -o Matrix.o
main: main.o Matrix.o
	g++ main.o Matrix.o -o main
test.o : test.cpp
	g++ -c test.cpp -o test.o
test : test.o Matrix.o
	g++ test.o Matrix.o -o test
	./test
run : main
	./main
clean : 
	rm -rf test main main.o test.o Matrix.o	