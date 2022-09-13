SRC=main.c
LIBS=OStools.c
HEADS=OStools.h 
CC=gcc

build: OStools.o
	$(CC) -o output OStools.o main.c

OStools.o:
	$(CC) -c -o OStools.o OStools.c
	
clean: 
	rm OStools.o
