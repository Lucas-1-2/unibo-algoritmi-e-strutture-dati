COMPILER := gcc
C_VERSION := c99
UTILITY_FILE := utility.c

all:
	compile run

compile:
	cd $(WORKING_FOLDER)
	$(COMPILER) -std=$(C_VERSION) -Wall -Wpedantic $(TO_COMPILE) -lm -o $(TO_COMPILE).exe

run:
	./$(TO_COMPILE).exe