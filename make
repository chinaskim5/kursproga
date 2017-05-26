.PHONY: all clean library

all: main.o
	gcc main.o -o main -ldl

main.o: main.c
	gcc -c main.c

library:sort
	
sort: mergesort.o shellsort.o
	gcc -shared mergesort.o shellsort.o -o sortlib.so
	
mergesort.o: mergesort.c
	gcc -fPIC -c mergesort.c
	
shellsort.o: shellsort.c
	gcc -fPIC -c shellsort.c
	
clean:
	rm -rf *.o
	

