all: doStuff

doStuff: main.c stuff.c stuff.h
	gcc -g main.c stuff.c sort.c sort_clean.c -o doStuff

run: doStuff
	./doStuff

valgrind: doStuff
	valgrind ./doStuff

checkStyle: main.c stuff.c stuff.h
	clint.py main.c stuff.c stuff.h sort_clean.c sort.c

clean:
	rm -rf doStuff
