CC = gcc
CFLAGS = -Wall
LDLIBS = -lm
PROG = tema1

build: $(PROG)

$(PROG): HashTable.o Main.o List.o Util.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

Main.o: Main.c

HashTable.o: Header.h HashTable.c

Util.o: Util.h Util.c

List.o: List.h List.c

.PHONY: clean

clean:
	rm -f *.o *~ tema1
