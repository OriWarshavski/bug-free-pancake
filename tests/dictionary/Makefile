CXX= g++
CC = $(CXX)

CXXFLAGS  = -pedantic -Wall -Werror -Wextra
CXXFLAGS += -g3
CXXFLAGS += -std=c++17

CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = utest.o
TARGET = utest

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

vala: $(TARGET)
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET) 2> vala.txt

hell: $(TARGET)
	valgrind  --tool=helgrind ./$(TARGET) 2> hell.txt
	
clang_check: CXX = clang++
clang_check: check

clean:
	@$(RM) ./$(TARGET) $(OBJS)

utest.cpp : $(INCLUDES_DIR)/dictionary.hpp $(INCLUDES_DIR)/mu_test.h

.PHONY : make clean check

make:
	@echo 'Attend a maker faire next year! now back to coding...'
	@${TRUE}
