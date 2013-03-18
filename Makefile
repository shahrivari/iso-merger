CFLAGS = -I.
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += --pedantic
CFLAGS += -O3
CFLAGS += -std=gnu99

CC = gcc

all: main

main: 
	$(CC) $(CFLAGS) -o saeed nautil.c  naugraph.c nautinv.c naurng.c  nauty.c  schreier.c main.c -lgmp

reducer:
	rm -f reducer
	$(CC) $(CFLAGS) -o reducer reducer.c
	
	
clean:
	rm -f saeed reducer *.o

# DO NOT DELETE
