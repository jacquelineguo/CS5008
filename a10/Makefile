all: mt_search

mt_search: mt_search.c
	gcc -pthread -o mt_search mt_search.c

run: mt_search
	./mt_search inputs/input1.txt 5 2 10

clean:
	rm example mt_search *~
