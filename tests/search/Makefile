CXX=g++
CC=$(CXX)

CFLAGS = -pedantic -Wall -Werror
CFLAGS += -g
CXXFLAGS = $(CFLAGS) -std=c++17

CPPFLAGS = -DDEBUG
CPPFLAGS += -I$(INCLUDES_DIR)

LDLIBS = -pthread

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src
INL_DIR = $(INCLUDES_DIR)/inl


OBJECT = utest.o $(SOURCES_DIR)/qury_cache.o $(SOURCES_DIR)/searcher.o $(SOURCES_DIR)/uiSearch.o $(SOURCES_DIR)/page.o $(SOURCES_DIR)/search_word_protocol.o

TARGET = utest

$(TARGET): $(OBJECT)

all: $(TARGET)

check: $(TARGET)
	@./$(TARGET) -v

recheck: clean check

vala: $(TARGET)
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET) 2> vala.txt

hell: $(TARGET)
	valgrind  --tool=helgrind ./$(TARGET) 2> hell.txt

clean:
	@$(RM) -f ./$(TARGET) *.o  $(SOURCES_DIR)/*.o *.txt

.PHONY: make clean check recheck all

make:
	@echo 'Attend a maker faire'
	@${TRUE}

utest.o: utest.cpp $(INCLUDES_DIR)/qury_cache.hpp $(INCLUDES_DIR)/searcher.hpp $(INCLUDES_DIR)/page.hpp

qury_cache.o: $(SOURCES_DIR)/qury_cache.cpp $(INCLUDES_DIR)/qury_cache.hpp $(INCLUDES_DIR)/page.hpp $(INCLUDES_DIR)/nicknames.hpp

searcher.o: $(SOURCES_DIR)/searcher.cpp $(INCLUDES_DIR)/searcher.hpp $(INCLUDES_DIR)/qury_cache.hpp $(INCLUDES_DIR)/uiSearch.hpp $(INL_DIR)/uiSearch.hxx $(INCLUDES_DIR)/page.hpp $(INCLUDES_DIR)/nicknames.hpp

page.o:  $(SOURCES_DIR)/page.cpp $(INCLUDES_DIR)/page.hpp

 search_word_protocol.o: $(SOURCES_DIR)/search_word_protocol.cpp $(INCLUDES_DIR)/search_word_protocol.hpp
