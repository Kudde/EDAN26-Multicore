CC	= cc
CFLAGS	= -std=c11 -pedantic -Wall -Werror -g -O3 -DTHREAD_STATS
LIBS	= -lpthreads -lm
OUT	= a.out
FILE	= sort

execute:
	gcc sort.c -std=c11 -pedantic -Wall -Werror -g -O3 -pthread
	./a.out


clean:
	rm -f *.s *.o $(OUT) output
