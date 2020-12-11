.POSIX:
.PHONY: run clean
CC= gcc
CFLAGS= -g -Wall -Wextra -Wpedantic -Wuninitialized -Wundef -Wcast-align -Wstrict-overflow=2 -Wwrite-strings -Wno-format-nonliteral
BINARY=rush
OBJECTS= input.o
LFLAGS= -lasan

$(BINARY): $(OBJECTS)
	$(CC) -o $(BINARY) $(OBJECTS) $(LFLAGS)

# rush.o: rush.c input.h
# 	$(CC) $(CFLAGS) -c rush.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

run: $(BINARY)
	./$(BINARY)

clean:
	rm *.o $(BINARY)
