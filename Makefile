CC=gcc
CFLAGS= -std=gnu99 -Wall -Werror

.PHONY: default clean

default: app.exe

fonction.o: fonction.c fonction.h
	$(CC) $(CFLAGS) -o fonction.o -c fonction.c

jeux.o: jeux.c fonction.h
	$(CC) $(CFLAGS) -o jeux.o -c jeux.c

app.exe: jeux.o fonction.o
	$(CC) $(CFLAGS) -o app.exe jeux.o fonction.o

clean:
	rm *.o
	rm app.exe