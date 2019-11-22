# Copyright 2019 Grama Nicolae

.PHONY: gitignore clean memory beauty run
.SILENT: beauty clean memory gitignore

# Compilation variables
CC = g++
CFLAGS = -Wno-unused-parameter -Wall -Wextra -pedantic -g -O3 -std=c++14
EXE = Tester
SRC = $(wildcard */*.cpp)
OBJ = $(SRC:.cpp=.o)

# Compiles the program
build: $(OBJ)
	$(info Compiling code...)
	@$(CC) -o $(EXE) $^ $(CFLAGS) ||:
	$(info Compilation successfull)
	-@rm -f */*.o ||:
	@$(MAKE) -s gitignore ||:

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) 

# Executes the binary
run: clean build
	./$(EXE) < input.txt

# Deletes the binary and object files
clean:
	rm -f $(EXE) $(OBJ) Homework.zip
	echo "Deleted the binary and object files"

# Automatic coding style, in my personal style
beauty:
	clang-format -i -style=file */*.cpp
	clang-format -i -style=file */*.hpp

# Checks the memory for leaks
MFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
memory:clean build
	valgrind $(MFLAGS) ./$(EXE) < input.txt

# Adds and updates gitignore rules
gitignore:
	@echo "$(EXE)" > .gitignore ||:
	@echo "sources/*.o" >> .gitignore ||:
	@echo ".vscode*" >> .gitignore ||:	
	echo "Updated .gitignore"
	
# Creates an archive of the project
pack: clean
	zip -FSr Homework.zip *

