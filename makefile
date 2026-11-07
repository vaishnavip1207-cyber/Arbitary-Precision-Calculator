CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = apc

OBJECTS = main.o common.o addition.o subtraction.o multiplication.o division.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

main.o: main.c apc.h
	$(CC) $(CFLAGS) -c main.c

common.o: common.c apc.h
	$(CC) $(CFLAGS) -c common.c

addition.o: addition.c apc.h
	$(CC) $(CFLAGS) -c addition.c

subtraction.o: subtraction.c apc.h
	$(CC) $(CFLAGS) -c subtraction.c

multiplication.o: multiplication.c apc.h
	$(CC) $(CFLAGS) -c multiplication.c

division.o: division.c apc.h
	$(CC) $(CFLAGS) -c division.c

clean:
	rm -f $(OBJECTS) $(TARGET)