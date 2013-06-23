CFLAGS = -I.
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += --pedantic
CFLAGS += -O3
CFLAGS += -std=gnu99

CC = gcc
JAVA_HOME="/cygdrive/c/Program\ Files/Java/jdk1.6.0_38/"

all: main

main: 
	$(CC) $(CFLAGS) -o saeed nautil.c  naugraph.c nautinv.c naurng.c  nauty.c  schreier.c main.c -lgmp

reducer:
	rm -f reducer
	$(CC) $(CFLAGS) -o reducer reducer.c
	
	
clean:
	rm -f saeed reducer *.o

jni:
	g++ -O3 -Wl,--add-stdcall-alias -I "/cygdrive/c/Program Files/Java/jdk1.6.0_38/include" -I"/cygdrive/c/Program Files/Java/jdk1.6.0_38/include/win32" -shared -o nauty.dll nautil.c  naugraph.c nautinv.c naurng.c  nauty.c  schreier.c nauty_jni.cpp


# DO NOT DELETE
