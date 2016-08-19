DIRS=lib
export CFLAGS=-Wall -g3 -DDEBUG3
INCLUDES=-I./include

all: main

main: install main.o
	gcc -o main *.o $(CFLAGS) $(INCLUDES)

main.o: main.c include/llist.h include/debug.h
	gcc -c -o $@ $< $(CFLAGS) $(INCLUDES)

install:
	 @ for dir in $(DIRS) ; do \
		make -C $$dir $@ ; \
	done

clean:
	rm *~ *.o main -f
	@ for dir in $(DIRS) ; do \
		make -C $$dir $@ ; \
	done

