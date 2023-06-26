$(CXX)=g++
$(CC)=$(CXX)

CFLAGS = -pedantic -Wall -Werror
CFLAGS += -g
CXXFLAGS = $(CFLAGS) -std=c++17

CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src


SOURCE := utest.cpp $(SOURCES_DIR)/color_image.cpp  $(SOURCES_DIR)/draw_primitives.cpp
TARGET := utest

all: $(TARGET)

$(TARGET) : $(SOURCE)

#$(SOURCE) : $(SOURCES_DIR)/color_image.cpp

check : $(TARGET) parrot.ppm
	@./$(TARGET) -v

recheck: clean check

parrot.ppm: img.zip
	unzip -o img.zip

clean:
	@$(RM) -f ./$(TARGET) *.o *.ppm


.PHONY : make clean check recheck all

make:
	@echo 'Attend a maker faire'
	@${TRUE}
