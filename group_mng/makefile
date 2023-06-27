#makefile GROUP_MNG
TARGET = groupMng.out
CC = gcc
CFLAGS = -ansi -g -pedantic
LIBRARY_PASS = ~/C/data_structure/library/
QUEUE_PATH = ~/C/data_structure/queue/
HASH_PATH = ~/C/data_structure/hash_map/
OBJ = groupMng.o groupMng_test.o

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) -L $(LIBRARY_PASS) -lgends -lm

groupMng.o: groupMng.c groupMng.h $(QUEUE_PATH)queueG.h $(HASH_PATH)hashMap.h
	$(CC) $(CFLAGS) -I $(QUEUE_PATH) -I $(HASH_PATH) -c groupMng.c

groupMng_test.o: groupMng_test.c groupMng.h
	$(CC) $(CFLAGS) -c groupMng_test.c

clean:
	rm -f $(TARGET) $(OBJ)

val:
	valgrind --log-file=V2.log --leak-check=full --track-origins=yes ./groupMng.out