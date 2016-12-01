
holiday: holiday.o graph.o
	gcc -o holiday holiday.o graph.o

graph.o: graph.c graph.h
	gcc -c -Wall graph.c

holiday.o: holiday.c holiday.h
	gcc -c -Wall holiday.c
