.POSIX:
.PHONY: run clean
CC= gcc
CFLAGS= -g -Wall -Wextra -Wpedantic -Wuninitialized -Wundef -Wcast-align -Wstrict-overflow=2 -Wwrite-strings -Wno-format-nonliteral
BINARY=rush
OBJECTS= main.o
LFLAGS= -lasan

$(BINARY): $(OBJECTS)
	$(CC) -o $(BINARY) $(OBJECTS) $(LFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

run: $(BINARY)
	./$(BINARY)

clean:
	rm *.o $(BINARY)
