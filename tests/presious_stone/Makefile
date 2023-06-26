CXX=g++
CC=$(CXX)

CFLAGS = -pedantic -Wall -Werror
CFLAGS += -g
CXXFLAGS = $(CFLAGS) -std=c++17

CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR) -I$(INC_PRECIOUS_DIR) 

INCLUDES_DIR = ../../inc
INC_PRECIOUS_DIR = ../../inc/precious_stone
SRC_PRECIOUS_DIR = ../../src/precious_stone
SOURCES_DIR = ../../src
INL_DIR = ../../inc/precious_stone/inl

INFRA = 	$(SRC_PRECIOUS_DIR)/massage.cpp \
			$(SRC_PRECIOUS_DIR)/link_box.cpp $(SRC_PRECIOUS_DIR)/hard_coded_input.cpp \
			$(SRC_PRECIOUS_DIR)/output_udp.cpp $(SRC_PRECIOUS_DIR)/input_udp.cpp $(SRC_PRECIOUS_DIR)/udp.cpp \
			$(SRC_PRECIOUS_DIR)/input_stream.cpp $(SRC_PRECIOUS_DIR)/output_stream.cpp \
			$(SRC_PRECIOUS_DIR)/caesar_convert.cpp \
			$(SRC_PRECIOUS_DIR)/input_file.cpp $(SRC_PRECIOUS_DIR)/output_file.cpp \
			$(SRC_PRECIOUS_DIR)/capitalize_convert.cpp \
			$(SRC_PRECIOUS_DIR)/vowel_censor_convert.cpp \
			$(SRC_PRECIOUS_DIR)/output_terminal.cpp \
			$(SRC_PRECIOUS_DIR)/input_terminal.cpp \

SOURCE = utest.cpp $(INFRA)
TARGET = utest

all: $(TARGET)

utest: $(SOURCE)

check : $(TARGET) texts
	@./$(TARGET) -v

recheck: clean check

texts: texts.zip
	unzip -o texts.zip

clean:
	@$(RM) -f ./$(TARGET) *.o *.txt 


.PHONY : make clean check recheck all

make:
	@echo 'Attend a maker faire'
	@${TRUE}
