# @file Makefile
# @author Mostafa Asaad
# @brief A makefile for the calculator project.

all: calculator.o operations.o
	gcc calculator.o operations.o -o calculator.exe

calculator.o: 
	gcc -c calculator.c -o calculator.o

operations.o:
	gcc -c operations\operations.c -o operations.o

clean:
	rm *.exe *.o
