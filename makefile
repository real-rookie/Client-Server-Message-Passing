CC = g++
C_FLAGS = -c -std=c++11 -g -Wall -O0

all: client server

client: client.o tands.o
	$(CC) -o client client.o tands.o
server: server.o tands.o
	$(CC) -o server server.o tands.o
client.o: client.cpp
	$(CC) $(C_FLAGS) client.cpp
server.o: server.cpp
	$(CC) $(C_FLAGS) server.cpp
tands.o: tands.c
	$(CC) $(C_FLAGS) tands.c

run:
	./$(main)
memcheck:
	valgrind --tool=memcheck --leak-check=full ./$(main)
clean:
	rm -f client server *.o