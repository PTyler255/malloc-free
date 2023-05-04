
palloc: ptest.c palloc.c
	gcc -o palloc ptest.c palloc.c -lm

clean:
	rm -f *.o
