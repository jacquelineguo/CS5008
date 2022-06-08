all:sort

sort: quicksort.c main.c algB.c algC.c algD.c
	gcc main.c quicksort.c algB.c algC.c algD.c -o sort

run: sort
	./sort

clean: 
	rm *# *~ sort
