CC = g++
CFLAGS = -g -Wall -O2

all:main

main:main.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONE: clean

clean:
	rm -f *.o main
