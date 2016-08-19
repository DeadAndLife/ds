CFLAGS+=-Wall -g3

all: llist.o debug.o

%.o: %.c ../include/llist.h ../include/debug.h
	gcc -c -o $@ $< $(CFLAGS)

install: all
	cp *.o ..

clean:
	rm *~ *.o -f
