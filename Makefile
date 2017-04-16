



CC=gcc
CFLAGS= -std=gnu99 -Wall -Werror


default:
	$(CC) $(CFLAGS) jeux.c -o  jeux
	$(CC) $(CFLAGS) jeuxS.c -o  jeuxS
	$(CC) $(CFLAGS) fonctionS.c -o  fonctionS
	$(CC) $(CFLAGS) Canon.c -o  Canon


