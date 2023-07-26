CXX=g++
CC=$(CXX)

CFLAGS = -ansi -pedantic -Wall -Werror -g -I$(INCLUDES_DIR) -std=c++17

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

SOURCE := utest.cpp $(SOURCES_DIR)/unitronics.c
TARGET = test

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS)

check: $(TARGET)
	@./$(TARGET)

clean:
	@$(RM) -f ./$(TARGET) *.o