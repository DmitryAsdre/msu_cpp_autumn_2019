main : main.o bigint.o
	g++ -g main.o bigint.o -o main
main.o : main.cpp
	g++ -c -g main.cpp -o main.o
bigint.o : BigInt.hpp BigInt.cpp
	g++ -c -g BigInt.cpp -o bigint.o
clean : 
	rm -rf main.o main bigint.o test.o test
test.o : test.cpp
	g++ -g test.cpp -c -o test.o
Test : bigint.o test.o
	g++ -g test.o bigint.o -o test
generate : 
	python3 generate.py
test : Test
	python3 test.py
run : main
	./main