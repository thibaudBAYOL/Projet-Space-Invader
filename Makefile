



CC=gcc
CFLAGS= -std=gnu99 -Wall -Werror


default:
	$(CC) $(CFLAGS) jeux.c -o  jeux
	$(CC) $(CFLAGS) jeuxS.c -o  jeuxS


