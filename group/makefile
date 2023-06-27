#makefile GROUP
TARGET = group.out
CC = gcc
CFLAGS = -ansi -g -pedantic
LIBRARY_PASS = ~/C/data_structure/library/
QUEUE_PATH = ~/C/data_structure/queue/
OBJ = group.o group_test.o

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) -L $(LIBRARY_PASS) -lgends -lm

group.o: group.c group.h
	$(CC) $(CFLAGS) -c group.c

group_test.o: group_test.c group.h
	$(CC) $(CFLAGS) -c group_test.c

clean:
	rm -f $(TARGET) $(OBJ)

val:
	valgrind --log-file=V2.log --leak-check=full --track-origins=yes ./group.out