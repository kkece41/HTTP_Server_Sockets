CC = gcc
CFLAGS = -Wall -g

server : TCP_Server.o common.o
	$(CC) $(CFLAGS) -o server common.o TCP_Server.o 

common.o : common.h common.c
	$(CC) $(CFLAGS) -c common.c

TCP_Server.o : TCP_Server.c common.h
	$(CC) $(CFLAGS) -c TCP_Server.c

clean:
	rm -rf server common.o TCP_Server.o
