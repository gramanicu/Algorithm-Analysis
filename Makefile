# Copyright 2019 Grama Nicolae

.PHONY: gitignore clean memory beauty run
.SILENT: beauty clean memory gitignore

# Compilation variables
CC = g++
CFLAGS = -Wno-unused-parameter -Wall -Wextra -pedantic -g -O3 -std=c++14
EXE = Tester
SRC = $(wildcard src/*.cpp)
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
	./$(EXE) 2>/dev/null 

# Deletes the binary and object files
clean:
	rm -f $(EXE) $(OBJ) ./out/*.out Homework.zip
	echo "Deleted the binary and object files"

# Automatic coding style, in my personal style
beauty:
	clang-format -i -style=file */*.cpp
	clang-format -i -style=file */*.hpp

# Checks the memory for leaks
MFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
memory:clean build
	valgrind $(MFLAGS) ./$(EXE)

# Adds and updates gitignore rules
gitignore:
	@echo "$(EXE)" > .gitignore ||:
	@echo "generator/Generator" >> .gitignore ||:
	@echo "src/*.o" >> .gitignore ||:
	@echo "generator/*.o" >> .gitignore ||:
	@echo ".vscode*" >> .gitignore ||:	
	@echo "in/*" >> .gitignore ||:	
	@echo "ref/*" >> .gitignore ||:	
	@echo "out/*" >> .gitignore ||:	
	@echo "other_tests/*" >> .gitignore ||:
	echo "Updated .gitignore"
	
# Creates an archive of the project
pack: clean
	zip -FSr Homework.zip *

