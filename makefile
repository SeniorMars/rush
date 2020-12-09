.POSIX:
.PHONY: run clean
CC= gcc
CFLAGS= -g -Wall -Wextra -Wpedantic -Wuninitialized -Wundef -Wcast-align -Wstrict-overflow=2 -Wwrite-strings -Wno-format-nonliteral
BINARY=rush
OBJECTS= rush.o
LFLAGS= -lasan

$(BINARY): $(OBJECTS)
	$(CC) -o $(BINARY) $(OBJECTS) $(LFLAGS)

rush.o: rush.c
	$(CC) $(CFLAGS) -c rush.c

run: $(BINARY)
	./$(BINARY)

clean:
	rm *.o $(BINARY)
