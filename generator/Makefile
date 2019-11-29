# Copyright 2019 Grama Nicolae

.PHONY: gitignore clean memory beauty run
.SILENT: beauty clean memory gitignore

# Compilation variables
CC = g++
CFLAGS = -Wno-unused-parameter -Wall -Wextra -pedantic -g -O3 -std=c++14
EXE = Generator
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
INP = ../in/*
REF = ../ref/*

# Compiles the program
build: $(OBJ)
	$(info Compiling code...)
	@$(CC) -o $(EXE) $^ $(CFLAGS) ||:
	$(info Compilation successfull)
	-@rm -f */*.o ||:

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) 

# Executes the binary
run: clean build
	./$(EXE)

# Deletes the binary and object files
clean:
	rm -f $(EXE) $(OBJ)
	echo "Deleted the binary and object files"

# Deletes the binary, object files and generated files
cleanAll:
	rm -f $(EXE) $(OBJ)
	rm -f $(INP)
	rm -f $(REF)
	echo "Deleted the binary binaries, object files and generated files"

# Automatic coding style, in my personal style
beauty:
	clang-format -i -style=file *.cpp
	clang-format -i -style=file *.hpp

# Checks the memory for leaks
MFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
memory:clean build
	valgrind $(MFLAGS) ./$(EXE)