all: main add.plugin

main: main.o
	gcc -o $@ $< -ldl

%.plugin: %.o
	gcc -shared -fPIC -o $@ $<

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *~ *.o *.plugin main
