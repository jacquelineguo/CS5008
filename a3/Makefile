all: sort

sort: sort.h sort.c linkedlist.c  main.c
	gcc main.c sort.c linkedlist.c -o sort

test: operationtest.h operationtest.c linkedlist.c main.c
	gcc -g maintest.c operationtest.c linkedlist.c -o operationtest

run: sort
	./sort

clean: 
	rm operationtest sort *.*~
