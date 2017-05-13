CC=gcc
CFLAGS= -std=gnu99 -Wall -Werror

.PHONY: default clean

default: app.exe

fonction.o: fonction.c fonction.h
	$(CC) $(CFLAGS) -o fonction.o -c fonction.c

canon.o: canon.c fonction.h
	$(CC) $(CFLAGS) -o canon.o -c canon.c

app.exe: canon.o fonction.o
	$(CC) $(CFLAGS) -o app.exe canon.o fonction.o

clean:
	rm *.o
	rm app.exe