all: tree

tree: queue.h queue.c stack.h stack.c tree.h tree.c main.c
	gcc queue.c stack.c tree.c main.c -o tree

run: tree
	./tree

clean:
	rm tree *~ *# *.gch
