#makefile
# Created on: 2013-11-25 下午4:00:00

CC = g++
CFLAGS = -g -Wall -O2

all:main

main:main.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONE: clean

clean:
	rm -f *.o main
