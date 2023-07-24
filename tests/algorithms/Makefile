CC = gcc

CFLAGS += -ansi -pedantic -Wall -Werror -g
CFLAGS +=  -I$(INCLUDES_DIR) -std=c99 -lm

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

SOURCE := test.c $(SOURCES_DIR)/algorithms.c 
TARGET = test

$(TARGET): $(SOURCE)
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS)

check: $(TARGET)
	@./$(TARGET)

clean: 
	@$(RM) -f ./$(TARGET) *.o