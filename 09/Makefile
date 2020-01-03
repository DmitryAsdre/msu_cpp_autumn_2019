main : main.cpp 
	g++ main.cpp -pthread -o main
tes : test.cpp	
	g++ test.cpp -o test
run : main
	./main
test : tes main
	./test
	make clean
clean : 
	rm -rf main test sorted.bin input 