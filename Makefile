CFLAGS=-g -O2 -Wall -Wextra  -std=c2x -pedantic $(OPTFLAGS)
CC=clang
MODULES_OBJECT_DIR=build/modules
MODULES_SOURCE_DIR=src/modules
MODULES_SOURCES=$(wildcard $(MODULES_SOURCE_DIR)/*.c )
MODULES_OBJECTS=$(patsubst $(MODULES_SOURCE_DIR)/%.c, $(MODULES_OBJECT_DIR)/%.o, $(MODULES_SOURCES))
SIMPLETRON_OBJECT=build/simpletron.o
SIMPLETRON_SOURCE=src/simpletron.c
SIMPLETRON_BIN=bin/simpletron

all: simpletron tests

simpletron: build $(SIMPLETRON_OBJECT) $(MODULES_OBJECTS) 
	$(CC) -o $(SIMPLETRON_BIN) $(CFLAGS) $(SIMPLETRON_OBJECT) $(MODULES_OBJECTS)
	@ctags -R .
$(SIMPLETRON_OBJECT): $(SIMPLETRON_SOURCE)
	$(CC) -c $(CFLAGS) $(SIMPLETRON_SOURCE) -o $(SIMPLETRON_OBJECT)
$(MODULES_OBJECTS): $(MODULES_OBJECT_DIR)/%.o: $(MODULES_SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

build:
	@mkdir -p build/modules
	@mkdir -p bin

.PHONY: tests
tests:
	make -f MakeCppUTest.mk all

clean:
	rm -rf bin
	rm -rf build
	rm -f *~
	rm -f *.*~
	rm -f src/*.*~
	rm -f src/modules/*.*~
	rm -rf test-obj
	rm -rf test-lib
	rm -f tests/*.*~
	rm -f simpletron_tests 
