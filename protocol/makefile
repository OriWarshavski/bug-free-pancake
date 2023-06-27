#makefile PROTOCOL
TARGET = protocol.out
CC = gcc
CFLAGS = -ansi -g -pedantic
LIBRARY_PASS = ~/work/data_structure/library/
LIST_PATH = ~/work/data_structure/linked_list/double_linked_generic/
OBJ = protocol.o protocol_test.o

$(TARGET): $(OBJ) $(TARGET)
	$(CC) -o $(TARGET) $(OBJ) -L $(LIBRARY_PASS) -lgends -lm

protocol.o: protocol.c protocol.h limit.h
	$(CC) $(CFLAGS) -c protocol.c

protocol_test.o: protocol_test.c protocol.h
	$(CC) $(CFLAGS) -c protocol_test.c

clean:
	rm -f $(TARGET) $(OBJ)

val:
	valgrind --log-file=V2.log --leak-check=full --track-origins=yes ./user.out
