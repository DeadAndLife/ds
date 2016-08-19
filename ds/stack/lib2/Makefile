all: main

main: main.o stack.o llist.o
	gcc -o main *.o

main.o: main.c stack.h llist.h
	gcc -c -o main.o main.c

stack.o: stack.c stack.h llist.h
	gcc -c -o stack.o stack.c

llist.o: llist.c llist.h
	gcc -c -o llist.o llist.c

clean:
	rm *.o *~ main -f
