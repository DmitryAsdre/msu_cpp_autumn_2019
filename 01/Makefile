all: clean calc test
calc : main.cpp
	g++ main.cpp -o calc
debug : main.cpp 
	g++ main.cpp -g -o calc
run : calc 
	./calc $(ARGS)
test : calc test.py
	python test.py
clean : 
	rm -rf calc

