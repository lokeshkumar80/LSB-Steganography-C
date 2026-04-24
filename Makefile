CC=gcc
CFLAGS=-Iinclude
LIBS=-lpng -lm
SRC=$(shell find src -name "*.c")

all:
	$(CC) $(SRC) -o stego $(CFLAGS) $(LIBS)

clean:
	rm -f stego
