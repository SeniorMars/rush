.POSIX:
.PHONY: run clean
CC= gcc
CFLAGS= -g -Wall -Wextra -Wpedantic -Wuninitialized -Wundef -Wcast-align -Wstrict-overflow=2 -Wwrite-strings -Wno-format-nonliteral
BINARY=rush
OBJECTS= rush.o input.o utils.o commandhandler.o
LFLAGS= -lasan

$(BINARY): $(OBJECTS)
	$(CC) -o $(BINARY) $(OBJECTS) $(LFLAGS)

rush.o: rush.c input.h commandhandler.h utils.h
	$(CC) $(CFLAGS) -c rush.c

input.o: input.c input.h utils.h
	$(CC) $(CFLAGS) -c input.c

commandhandler.o: commandhandler.c commandhandler.h utils.h
	$(CC) $(CFLAGS) -c commandhandler.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

run: $(BINARY)
	./$(BINARY)

clean:
	rm *.o $(BINARY)
