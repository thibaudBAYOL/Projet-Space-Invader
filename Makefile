



CC=gcc
CFLAGS= -std=gnu99 -Wall -Werror




default: f
	$(CC) $(CFLAGS) jeux.c -o  jeux
	$(CC) $(CFLAGS) jeuxS.c -o  jeuxS
	$(CC) $(CFLAGS) Canon.c -o  C




fonction.o: fonction.c fonction.h
	$(CC) $(CFLAGS) -o fonction.o -c fonction.c 

f: fonction.o 
	$(CC) $(CFLAGS) -o f fonction.o


clean:
	rm *.o

