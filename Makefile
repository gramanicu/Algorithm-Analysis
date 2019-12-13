# Copyright 2019 Grama Nicolae

.PHONY: gitignore clean memory beauty run
.SILENT: beauty clean memory gitignore

# Compilation variables
CC = g++
CFLAGS = -Wno-unused-parameter -Wall -Wextra -pedantic -g -O3 -std=c++14
EXE = algo_test
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

# Compiles the object files
build: algo.o algo1.o algo2.o algo3.o
	$(info Compilation successfull)

# Compiles the program
build_test: algo_test.o algo.o algo1.o algo2.o algo3.o
	$(info Compiling code...)
	@$(CC) -o $(EXE) $^ $(CFLAGS) ||:
	$(info Compilation successfull)
	-@rm -f *.o ||:
	@$(MAKE) -s gitignore ||:

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) 

# Executes the binary
run: clean build_test
	./$(EXE)

# Deletes the binary and object files
clean:
	rm -f $(EXE) $(OBJ) ./src/*.o ./out/*.out Homework.zip
	echo "Deleted the binary and object files"

# Automatic coding style, in my personal style
beauty:
	clang-format -i -style=file *.cpp
	clang-format -i -style=file *.h

# Checks the memory for leaks
MFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
memory:clean build
	valgrind $(MFLAGS) ./$(EXE)

# Adds and updates gitignore rules
gitignore:
	@echo "$(EXE)" > .gitignore ||:
	@echo "generator/generator" >> .gitignore ||:
	@echo "in/*" >> .gitignore ||:
	@echo "*.o" >> .gitignore ||:
	@echo "generator/*.o" >> .gitignore ||:
	@echo ".vscode*" >> .gitignore ||:	
	@echo "out/*" >> .gitignore ||:	
	@echo "other_tests/*" >> .gitignore ||:
	echo "Updated .gitignore"

graphs:
	python graphs.py

# Builds tests, runs the solver and then generates the graphs
full_test:
	cd ./generator/ && \
	make run
	make run
	make graphs

# Creates an archive of the project
pack: clean
	zip -FSr Homework.zip algo.h algo.cpp ./generator ./src ./in ./out Makefile Readme.md
