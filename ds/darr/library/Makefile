CFLAGS+=-Wall -DDEBUG3 -I/usr/local/include

#all: install.dylib main
all: install.a main

#main: main.o debug.o libdarr.dylib
main: main.o debug.o libdarr.a
	gcc $(CFLAGS) -o $@ $^ -L /usr/local/lib -ldarr

lib%.a: %.o debug.o
	ar -cr $@ $<

lib%.dylib: %.o debug.o
	gcc -dynamiclib -o $@ debug.o $< $(CFLAGS)

%.o: %.c debug.h
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -f *~ *.o *.a *.dylib main

install.a: libdarr.a
	sudo cp *.a /usr/local/lib
	sudo cp darr.h /usr/local/include

install.dylib: libdarr.dylib
	sudo cp *.dylib /usr/local/lib
	sudo cp darr.h /usr/local/include

uninstall:
	sudo rm -f /usr/local/lib/libdarr.a /usr/local/lib/libdarr.dylib
	sudo rm -f /usr/local/include/darr.h
