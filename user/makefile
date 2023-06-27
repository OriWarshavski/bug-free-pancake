#makefile USER
TARGET = user.out
CC = gcc
CFLAGS = -ansi -g -pedantic
LIBRARY_PASS = ~/work/data_structure/library
HASH_PATH = ~/work/data_structure/hash_map/
OBJ = user.o user_test.o

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) -L $(LIBRARY_PASS) -lgends -lm

user.o: user.c user.h $(HASH_PATH)hashMap.h limit.h
	$(CC) $(CFLAGS) -I $(HASH_PATH) -c user.c

user_test.o: user_test.c $(HASH_PATH)hashMap.h
	$(CC) $(CFLAGS) -I $(HASH_PATH) -c user_test.c

clean:
	rm -f $(TARGET) $(OBJ)

val:
	valgrind --log-file=V2.log --leak-check=full --track-origins=yes ./user.out
