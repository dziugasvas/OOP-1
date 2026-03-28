all: create

create:
	g++ -std=c++17 main.cpp funkcijos.cpp -o programa

run: create
	./programa

clean:
	rm -f programa