CC          =	gcc

CFLAGS      =	-Wall -std=c99 -pedantic -g

test: src/balancedTreeImpl.c src/testTree.c src/test.c
	$(CC) $(CFLAGS) src/balancedTreeImpl.c src/testTree.c src/test.c -Iinclude -o bin/testMe

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm bin/*
