CXX=g++
CC=$(CXX)

CFLAGS = -pedantic -Wall -Werror
CFLAGS += -g
CXXFLAGS = $(CFLAGS) -std=c++17

CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src
INL_DIR = ../../inc/inl

SOURCE := utest.cpp
TARGET := utest

all: $(TARGET)

$(SOURCE) : $(INCLUDES_DIR)/algorithms.hpp $(INCLUDES_DIR)/generic_utils.hpp $(INL_DIR)/algorithms.hxx

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) -f ./$(TARGET) *.o


.PHONY : make clean check recheck all

make:
	@echo 'Attend a maker faire'
	@${TRUE}
