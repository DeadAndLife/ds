all: main load list_save list_load adt_save adt_load

adt_load: adt_load.o
	gcc -o $@ $<

adt_save: adt_save.o
	gcc -o $@ $<

list_load: list_load.o
	gcc -o list_load list_load.o

list_save: list_save.o
	gcc -o list_save list_save.o

load: load.o queue.o llist.o
	gcc -o load load.o queue.o llist.o

main: main.o queue.o llist.o
	gcc -o main main.o queue.o llist.o

%.o: %.c queue.h llist.h
	gcc -c -o $@ $<

clean:
	-rm *.o *~ main tmp load -f
	-rm -f adt_load adt_save list_load list_save
