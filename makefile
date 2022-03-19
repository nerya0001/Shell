CC=gcc
FLAGS=-Wall -g

all: main server

main: main.o libutil.a server.o client.o 
	$(CC) $(FLAGS) main.o libutil.a client.o -o main

server: server.o
	$(CC) $(FLAGS) server.o -o server

libutil.a: util.o
	$(AR) -rcs libutil.a util.o

server.o: server.c util.h
	$(CC) $(FLAGS) -c server.c

client.o: client.c util.h
	$(CC) $(FLAGS) -c client.c

main.o: main.c util.h
	$(CC) $(FLAGS) -c main.c

util.o: util.c util.h
	$(CC) $(FLAGS) -c util.c	



.PHONY: clean all

clean:
	rm -f *.o *.a main server client



