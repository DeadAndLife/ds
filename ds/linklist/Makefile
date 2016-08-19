all: main
CFLAGS+=-g -Wall

main: main.o llist.o

%.o: %.c llist.h
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm *~ *.o main -f
