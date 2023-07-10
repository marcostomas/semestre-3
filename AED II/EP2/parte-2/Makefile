all: run clean
run: run.o implementation.o repository.o aux.o print.o
	gcc -w run.o implementation.o repository.o aux.o print.o -o run

run.o: run.c headers.h aux.c print.c implementation.c
	gcc -g -w -c run.c -D t=$(t) 

implementation.o: implementation.c headers.h repository.c aux.c print.c
	gcc -g -w -c implementation.c -D t=$(t) 

repository.o: repository.c headers.h print.c
	gcc -g -w -c repository.c -D t=$(t) 

aux.o: aux.c headers.h implementation.c repository.c
	gcc -g -w -c aux.c -D t=$(t) 

print.o: print.c headers.h repository.c
	gcc -g -w -c print.c -D t=$(t) 

clean:
	rm -rf *.o

clear:
	rm -rf *.o
	rm -rf *.dat
	rm run
	clear