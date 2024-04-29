all: problem_2.o linked_list.o
	gcc problem_2.o linked_list.o -o out.exe
problem_2.o:
	gcc -c problem_2.c -o problem_2.o
linked_list.o:
	gcc -c Linked_List/single_linked_list.c -o linked_list.o
clean:
	rm *.o out.exe
