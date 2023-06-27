#makefile USER_MNG
TARGET = userMng.out
CC = gcc
CFLAGS = -ansi -g -pedantic
LIBRARY_PASS = ~/C/data_structure/library/
HASH_PATH = ~/C/data_structure/hash_map/
LIST_PATH = ~/C/data_structure/linked_list/double_linked_generic/
OBJ = usermng.o userMng_test.o user.o

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) -L $(LIBRARY_PASS) -lgends -lm

usermng.o: usermng.c usermng.h $(HASH_PATH)hashMap.h ../user/user.h limit.h $(LIST_PATH)listG.h
	$(CC) $(CFLAGS) -I $(HASH_PATH) -I ../user/ -I $(LIST_PATH) -c usermng.c

userMng_test.o: userMng_test.c $(HASH_PATH)hashMap.h $(LIST_PATH)listG.h
	$(CC) $(CFLAGS) -I $(HASH_PATH) -I $(LIST_PATH) -c userMng_test.c

user.o: ../user/user.c ../user/user.h $(HASH_PATH)hashMap.h limit.h
	$(CC) $(CFLAGS) -I ../user/ -I $(HASH_PATH) -c ../user/user.c

clean:
	rm -f $(TARGET) $(OBJ)

val:
	valgrind --log-file=V2.log --leak-check=full --track-origins=yes ./userMng.out