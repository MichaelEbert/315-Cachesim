CC = gcc
CFLAGS = -mtune=native -march=native -msse2 -O3 -std=c99 
default:
	$(CC) $(CFLAGS) lab6.c -o lab6