main: main.cpp
	g++ -std=c++2a *.cpp -o main

clean:
	clang++ -MJ a.o.json -Wall -std=c++2a -o a.o -c *.cpp
	rm a.o.json a.o
