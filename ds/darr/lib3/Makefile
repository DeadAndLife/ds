CFLAGS+=-Wall -DDEBUG1

all: main 

main: main.o darr.a debug.o
	gcc -o $@ $^ $(CFLAGS)

%.a: %.o
	ar -cr $@ $<

%.o: %.c darr.h debug.h
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -f *~ *.o *.a main
