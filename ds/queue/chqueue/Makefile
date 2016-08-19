all: main

main: main.o queue.o

%.o: %.c queue.h
	gcc -c -o $@ $< -Wall

clean:
	rm *~ *.o main -f
